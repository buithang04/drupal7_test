<?php
function cassiopeia_reports_page_list() {
  $records = cassiopeia_reports_get_all();

  return _cassiopeia_render_theme(
    "module",
    "cassiopeia_reports",
    "templates/page-report-list.tpl.php",
    array(
      'records' => $records,
    )
  );
}

function cassiopeia_reports_get_all() {
  return db_select('report_count_employee', 'rce')
    ->fields('rce', array(
      'id',
      'department_id',
      'department_name',
      'total_employees'
    ))
    ->orderBy('id', 'ASC')
    ->execute()
    ->fetchAll();
}






function cassiopeia_reports_department_added($department) {
  // report_count_employee
  db_insert('report_count_employee')
    ->fields(array(
      'department_id'   => $department['department_id'],
      'department_name' => $department['department_name'],
      'total_employees' => 0,
    ))
    ->execute();

  // report_count_task
  db_insert('report_count_task')
    ->fields(array(
      'department_id'   => $department['department_id'],
      'department_name' => $department['department_name'],
      'total_tasks'  => 0,
    ))
    ->execute();

  // report_employee_task
  db_insert('report_employee_task')
    ->fields([
      'department_id' => $department['department_id'],
      'department_name' => $department['department_name'],
      'task_ids' => '',
      'task_names' => '',
      'employee_ids' => '',
      'employee_names' => '',
    ])
    ->execute();
}

function cassiopeia_reports_department_updated($department) {
  // report_count_employee
  db_update('report_count_employee')
    ->fields(array(
      'department_name' => $department['department_name'],
    ))
    ->condition('department_id', $department['department_id'])
    ->execute();

  // report_count_task
  db_update('report_count_task')
    ->fields(array(
      'department_name' => $department['department_name'],
    ))
    ->condition('department_id', $department['department_id'])
    ->execute();

  // report_employee_task
  db_update('report_employee_task')
    ->fields([
      'department_name' => $department['department_name'],
    ])
    ->condition('department_id', $department['department_id'])
    ->execute();
}

function cassiopeia_reports_department_delete($department_id) {
  // report_count_employee
  db_delete('report_count_employee')
    ->condition('department_id', $department_id)
    ->execute();

  // report_count_task
  db_delete('report_count_task')
    ->condition('department_id', $department_id)
    ->execute();

  // report_employee_task
  db_delete('report_employee_task')
    ->condition('department_id', $department_id)
    ->execute();
}

function cassiopeia_reports_employee_add($employee) {

  _cassiopeia_reports_update_count($employee['department_id'], 1);

 
  $r = db_select('report_employee_task', 'r')
    ->fields('r')
    ->condition('department_id', $employee['department_id'])
    ->execute()
    ->fetchObject();

  if (!$r) {
    // no report row for department (should not happen if department_added creates it), skip safe.
    return;
  }

  list($ids, $names) = csv_add(
    $r->employee_ids,
    $r->employee_names,
    $employee['employee_id'],
    $employee['employee_name']
  );

  db_update('report_employee_task')
    ->fields(['employee_ids' => $ids, 'employee_names' => $names])
    ->condition('department_id', $employee['department_id'])
    ->execute();
}

function cassiopeia_reports_employee_deleted($employee_id) {

  $employee = db_select('employees', 'e')
    ->fields('e', array('department_id'))
    ->condition('employee_id', $employee_id)
    ->execute()
    ->fetchObject();

  if (!$employee) return;

  _cassiopeia_reports_update_count($employee->department_id, -1);

  $r = db_select('report_employee_task', 'r')
    ->fields('r')
    ->condition('department_id', $employee->department_id)
    ->execute()
    ->fetchObject();

  if (!$r) return;

  list($ids, $names) = csv_remove(
    $r->employee_ids,
    $r->employee_names,
    $employee_id
  );

  db_update('report_employee_task')
    ->fields(['employee_ids' => $ids, 'employee_names' => $names])
    ->condition('department_id', $employee->department_id)
    ->execute();
}


function cassiopeia_reports_employee_updated($new, $old) {
  $old_dep = isset($old->department_id) ? $old->department_id : NULL;
  $new_dep = isset($new['department_id']) ? $new['department_id'] : NULL;

  if (empty($new['employee_id'])) return;
  if ($old_dep === $new_dep) {
    $r = db_select('report_employee_task', 'r')
      ->fields('r')
      ->condition('department_id', $new_dep)
      ->execute()
      ->fetchObject();

    if (!$r) return;

    $new_names = csv_update_name(
      $r->employee_ids,
      $r->employee_names,
      $new['employee_id'],
      $new['employee_name']
    );

    db_update('report_employee_task')
      ->fields(['employee_names' => $new_names])
      ->condition('department_id', $new_dep)
      ->execute();

    return;
  }
  if ($old_dep !== NULL) {

    _cassiopeia_reports_update_count($old_dep, -1);
  }
  if ($new_dep !== NULL) {
    _cassiopeia_reports_update_count($new_dep, 1);
  }

  if ($old_dep !== NULL) {
    $r_old = db_select('report_employee_task', 'r')
      ->fields('r')
      ->condition('department_id', $old_dep)
      ->execute()
      ->fetchObject();

    if ($r_old) {
      list($ids_old, $names_old) = csv_remove(
        $r_old->employee_ids,
        $r_old->employee_names,
        $new['employee_id']
      );

      db_update('report_employee_task')
        ->fields(['employee_ids' => $ids_old, 'employee_names' => $names_old])
        ->condition('department_id', $old_dep)
        ->execute();
    }
  }

 
 if ($new_dep !== NULL) {

  $r_new = db_select('report_employee_task', 'r')
    ->fields('r')
    ->condition('department_id', $new_dep)
    ->execute()
    ->fetchObject();

  if ($r_new) {
    list($ids_new, $names_new) = csv_add(
      $r_new->employee_ids,
      $r_new->employee_names,
      $new['employee_id'],
      $new['employee_name']
    );

    db_update('report_employee_task')
      ->fields(['employee_ids' => $ids_new, 'employee_names' => $names_new])
      ->condition('department_id', $new_dep)
      ->execute();
  }
}
}



function _cassiopeia_reports_update_count($department_id, $amount = 1) {
  db_update('report_count_employee')
    ->expression('total_employees', 'total_employees + :amount', array(':amount' => $amount))
    ->condition('department_id', $department_id)
    ->execute();
}


function cassiopeia_reports_page_task_list() {
  $records = cassiopeia_reports_get_all_tasks();

  return _cassiopeia_render_theme(
    "module",
    "cassiopeia_reports",
    "templates/page-report-task-list.tpl.php",
    array(
      'records' => $records,
    )
  );
}

function cassiopeia_reports_get_all_tasks() {
  return db_select('report_count_task', 'rcp')
    ->fields('rcp')
    ->orderBy('id', 'ASC')
    ->execute()
    ->fetchAll();
}


function cassiopeia_reports_task_added($task) {
 
  _cassiopeia_reports_update_task_count($task['department_id'], 1);


  $row = db_select('report_employee_task', 'r')
    ->fields('r')
    ->condition('department_id', $task['department_id'])
    ->execute()
    ->fetchObject();

  if (!$row) return;

  list($new_ids, $new_names) = csv_add(
    $row->task_ids,
    $row->task_names,
    $task['task_id'],
    $task['task_name']
  );

  db_update('report_employee_task')
    ->fields([
      'task_ids' => $new_ids,
      'task_names' => $new_names
    ])
    ->condition('department_id', $task['department_id'])
    ->execute();
}


function cassiopeia_reports_task_updated($new, $old) {
  if (empty($new['task_id'])) return;

  $old_department = isset($old->department_id) ? $old->department_id : NULL;
  $new_department = isset($new['department_id']) ? $new['department_id'] : NULL;

  
  if ($old_department === $new_department) {
    if ($new_department === NULL) return;

    $r = db_select('report_employee_task', 'r')
      ->fields('r')
      ->condition('department_id', $new_department)
      ->execute()
      ->fetchObject();

    if (!$r) return;

    $new_names = csv_update_name(
      $r->task_ids,
      $r->task_names,
      $new['task_id'],
      $new['task_name']
    );

    db_update('report_employee_task')
      ->fields(['task_names' => $new_names])
      ->condition('department_id', $new_department)
      ->execute();

    return;
  }

  if ($old_department !== NULL) {
    _cassiopeia_reports_update_task_count($old_department, -1);
  }
  if ($new_department !== NULL) {
    _cassiopeia_reports_update_task_count($new_department, +1);
  }


  if ($old_department !== NULL) {
    $r_old = db_select('report_employee_task', 'r')
      ->fields('r')
      ->condition('department_id', $old_department)
      ->execute()
      ->fetchObject();

    if ($r_old) {
      list($ids, $names) = csv_remove($r_old->task_ids, $r_old->task_names, $new['task_id']);

      db_update('report_employee_task')
        ->fields(['task_ids' => $ids, 'task_names' => $names])
        ->condition('department_id', $old_department)
        ->execute();
    }
  }


if ($new_department !== NULL) {

  $r_new = db_select('report_employee_task', 'r')
    ->fields('r')
    ->condition('department_id', $new_department)
    ->execute()
    ->fetchObject();

  if ($r_new) {
    list($ids_new, $names_new) = csv_add(
      $r_new->task_ids,
      $r_new->task_names,
      $new['task_id'],
      $new['task_name']
    );

    db_update('report_employee_task')
      ->fields([
        'task_ids' => $ids_new,
        'task_names' => $names_new,
      ])
      ->condition('department_id', $new_department)
      ->execute();
  }
}
}


function cassiopeia_reports_task_deleted($task_id) {
  if (empty($task_id)) return;

  $task = db_select('tasks', 't')
    ->fields('t', array('department_id'))
    ->condition('task_id', $task_id)
    ->execute()
    ->fetchObject();

  if (!$task) return;

  _cassiopeia_reports_update_task_count($task->department_id, -1);

  $r = db_select('report_employee_task', 'r')
    ->fields('r')
    ->condition('department_id', $task->department_id)
    ->execute()
    ->fetchObject();

  if (!$r) return;

  list($ids, $names) = csv_remove(
    $r->task_ids,
    $r->task_names,
    $task_id
  );

  db_update('report_employee_task')
    ->fields([
      'task_ids' => $ids,
      'task_names' => $names,
    ])
    ->condition('department_id', $task->department_id)
    ->execute();
}


function _cassiopeia_reports_update_task_count($department_id, $amount = 1) {
  db_update('report_count_task')
    ->expression('total_tasks', 'total_tasks + :amount', array(':amount' => $amount))
    ->condition('department_id', $department_id)
    ->execute();
}

function cassiopeia_reports_page_employee_task() {
  $items_per_page = 5;

  $query = db_select('report_employee_task', 'r')
    ->fields('r')
    ->orderBy('department_id', 'ASC');

  $pager = $query->extend('PagerDefault')->limit($items_per_page);

  // Lấy dữ liệu
  $records = $pager->execute()->fetchAll();

  return _cassiopeia_render_theme(
    "module",
    "cassiopeia_reports",
    "templates/page-report-employee-task.tpl.php",
    array(
      'records'     => $records,
    )
  );
}


/* =========================
   CSV helpers (simple & parallel)
   ========================= */

/**
 * Add id+name to parallel CSV lists (ids,names)
 * returns array(ids_csv, names_csv)
 */
function csv_add($ids, $names, $id, $name) {
  $arr_ids = $ids ? explode(',', $ids) : [];
  $arr_names = $names ? explode(',', $names) : [];

  if (!in_array((string)$id, $arr_ids, TRUE)) {
    $arr_ids[] = (string)$id;
    $arr_names[] = (string)$name;
  }
  return [implode(',', $arr_ids), implode(',', $arr_names)];
}

/**
 * Remove id & its parallel name from csv lists.
 * returns array(ids_csv, names_csv)
 */
function csv_remove($ids, $names, $id) {
  $arr_ids = $ids ? explode(',', $ids) : [];
  $arr_names = $names ? explode(',', $names) : [];

  $new_ids = [];
  $new_names = [];

  foreach ($arr_ids as $i => $v) {
    if ((string)$v !== (string)$id) {
      $new_ids[] = $v;
      $new_names[] = isset($arr_names[$i]) ? $arr_names[$i] : '';
    }
  }
  return [implode(',', $new_ids), implode(',', $new_names)];
}

/**
 * Update name for id in parallel csv lists.
 * returns names_csv
 */
function csv_update_name($ids, $names, $id, $new_name) {
  $arr_ids = $ids ? explode(',', $ids) : [];
  $arr_names = $names ? explode(',', $names) : [];

  foreach ($arr_ids as $i => $v) {
    if ((string)$v === (string)$id) {
      $arr_names[$i] = (string)$new_name;
      break;
    }
  }
  return implode(',', $arr_names);
}



