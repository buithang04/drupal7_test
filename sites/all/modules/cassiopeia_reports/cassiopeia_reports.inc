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
  db_insert('report_count_employee')
    ->fields(array(
      'department_id'   => $department['department_id'],
      'department_name' => $department['department_name'],
      'total_employees' => 0,
    ))
    ->execute();

  db_insert('report_count_task')
    ->fields(array(
      'department_id'   => $department['department_id'],
      'department_name' => $department['department_name'],
      'total_tasks'  => 0,
    ))
    ->execute();
}

function cassiopeia_reports_department_updated($department) {
  db_update('report_count_employee')
    ->fields(array(
      'department_name' => $department['department_name'],
    ))
    ->condition('department_id', $department['department_id'])
    ->execute();

    db_update('report_count_task')
    ->fields(array(
      'department_name' => $department['department_name'],
    ))
    ->condition('department_id', $department['department_id'])
    ->execute();
}

function cassiopeia_reports_department_delete($department_id) {
  db_delete('report_count_employee')
    ->condition('department_id', $department_id)
    ->execute();

    db_delete('report_count_task')
    ->condition('department_id', $department_id)
    ->execute();
}

// employ

function cassiopeia_reports_employee_add($employee) {
  _cassiopeia_reports_update_count($employee['department_id'], 1);
}

function cassiopeia_reports_employee_deleted($employee_id) {
  $employee = db_select('employees', 'e')
    ->fields('e', array('department_id'))
    ->condition('employee_id', $employee_id)
    ->execute()
    ->fetchObject();

  if ($employee) {
    _cassiopeia_reports_update_count($employee->department_id, -1);
  }
}

function cassiopeia_reports_employee_updated($new, $old) {

  $old_department = $old->department_id;
  $new_department = $new['department_id'];

  if ($old_department == $new_department) {
    return;
  }
  _cassiopeia_reports_update_count($old_department, -1);
  _cassiopeia_reports_update_count($new_department, 1);
}



function _cassiopeia_reports_update_count($department_id, $amount = 1) {
  db_update('report_count_employee')
    ->expression('total_employees', 'total_employees + :amount', array(':amount' => $amount))
    ->condition('department_id', $department_id)
    ->execute();
}


// task

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
}

function cassiopeia_reports_task_updated($new, $old) {

  $old_department = $old->department_id;
  $new_department = $new['department_id'];

  if ($old_department == $new_department) {
    return;
  }

  _cassiopeia_reports_update_task_count($old_department, -1);

  _cassiopeia_reports_update_task_count($new_department, 1);
}

function cassiopeia_reports_task_deleted($task_id) {

  $task = db_select('tasks', 'p')
    ->fields('p', array('department_id'))
    ->condition('task_id', $task_id)
    ->execute()
    ->fetchObject();

  if ($task) {
    _cassiopeia_reports_update_task_count($task->department_id, -1);
  }
}
function _cassiopeia_reports_update_task_count($department_id, $amount = 1) {
  db_update('report_count_task')
    ->expression('total_tasks', 'total_tasks + :amount', array(':amount' => $amount))
    ->condition('department_id', $department_id)
    ->execute();
}




