<?php
function cassiopeia_tasks_list() {

    $tasks = cassiopeia_tasks_get_all() ;

    return _cassiopeia_render_theme("module","cassiopeia_tasks","templates/page-tasks.tpl.php", ['tasks' => $tasks]);

}

function cassiopeia_tasks_get_all() {

    $query = db_select('tasks', 'e');

    $query->leftJoin('departments', 'c', 'c.department_id = e.department_id');

    $query->fields('e', ['task_id','task_name', 'task_desc', 'department_id']);
    $query->fields('c', ['department_name']);
    
    return $query->execute()->fetchAll() ;
}

function cassiopeia_tasks_delete($task_id) {


  module_invoke_all('task_deleted', $task_id);

  db_delete('tasks')
    ->condition('task_id', $task_id)
    ->execute();

  drupal_goto('quan-ly-du-an');

}

function cassiopeia_tasks_department_deleted($department_id){
      db_delete('tasks')
    ->condition('department_id', $department_id)
    ->execute();
}

function cassiopeia_tasks_form($form, &$form_state, $task_id = 0) {

  $task_data = [];

  if ($task_id) {
    $query = db_select('tasks', 't');
    $query->fields('t');
    $query->leftJoin('departments', 'd', 'd.department_id = t.department_id');
    $query->addField('d', 'department_name');
    $query->condition('t.task_id', $task_id);
    $task_data = $query->execute()->fetchAssoc();
  }

  $form['wrapper'] = [
    '#type' => 'container',
    '#attributes' => ['class' => ['task-form-wrapper']],
  ];

  $form['wrapper']['task_id'] = [
      '#type'  => 'hidden',
      '#default_value' => $task_id ? $task_data['task_id'] : 0,
      '#attributes' => [
          'id' => 'edit-task-id',
          'name' => 'task_id',
      ],
  ];

  $form['wrapper']['task_name'] = [
    '#type' => 'textfield',
    '#title' => t('Tên dự án'),
    '#required' => TRUE,
    '#default_value' => isset($task_data['task_name']) ? $task_data['task_name'] : '',
    '#attributes' => [
      'placeholder' => 'Nhập tên dự án',
      'id' => 'edit-task-name'
    ],
    '#prefix' => "<div class='input-wrap'>",
    '#suffix' => "</div>",
  ];

  $form['wrapper']['task_desc'] = [
    '#type' => 'textfield',
    '#title' => t('Mô tả dự án'),
    '#required' => FALSE,
    '#default_value' => isset($task_data['task_desc']) ? $task_data['task_desc'] : '',
    '#attributes' => [
      'placeholder' => 'Nhập mô tả dự án',
      'id' => 'edit-task-desc'
    ],
    '#prefix' => "<div class='input-wrap'>",
    '#suffix' => "</div>",
  ];

  $options = cassiopeia_departments_get_options();

  $form['wrapper']['department_id'] = [
    '#type' => 'select',
    '#title' => t('Chọn phòng ban'),
    '#options' => $options,
    '#default_value' => isset($task_data['department_id']) ? $task_data['department_id'] : '',
    '#attributes' => ['id' => 'edit-task-department'],
    '#prefix' => "<div class='input-wrap'>",
    '#suffix' => "</div>",
  ];

  $form['wrapper']['submit'] = [
    '#type' => 'submit',
    '#value' => $task_id ? t('Cập nhật') : t('Thêm mới'),
    '#prefix' => "<div class='form-buttons'>",
    '#suffix' => "</div>",
  ];

  return $form;
}


function cassiopeia_tasks_form_submit($form, &$form_state){
    $values = $form_state['values'];

    if(!empty($values['task_id']) && $values['task_id'] > 0 ){

      $old_task = db_select('tasks', 't')
        ->fields('t')
        ->condition('task_id', $values['task_id'])
        ->execute()
        ->fetchObject();

      db_update('tasks')
        ->fields(array(
          'task_name'     => $values['task_name'],
          'task_desc'     => $values['task_desc'],
          'department_id' => $values['department_id'],
        ))
        ->condition('task_id', $values['task_id'])
        ->execute();

      drupal_set_message(t('Cập nhật dự án thành công.'));

      $new_task = array(
        'task_id'       => $values['task_id'],
        'task_name'     => $values['task_name'],
        'task_desc'     => $values['task_desc'],
        'department_id' => $values['department_id'],
      );
      module_invoke_all('task_updated', $new_task, $old_task);

    } else { 

        $task_id = db_insert('tasks')
        ->fields([
            'task_name' => $values['task_name'],
            'task_desc' => $values['task_desc'],
            'department_id'=> $values['department_id'],
        ])
        ->execute();

        drupal_set_message(t('Thêm mới dự án thành công.'));

        $task = [
            'task_id' => $task_id,
            'task_name' => $values['task_name'],
            'task_desc' => $values['task_desc'],
            'department_id'=> $values['department_id'],
        ];

        module_invoke_all('task_added', $task);
    }

    $form_state['redirect'] = 'quan-ly-du-an';
}
