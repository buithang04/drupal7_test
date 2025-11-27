<?php
function cassiopeia_employees_list() {

    $employees = cassiopeia_employees_get_all() ;

    return _cassiopeia_render_theme("module","cassiopeia_employees","templates/page-employees.tpl.php", ['employees' => $employees]);

}

function cassiopeia_employees_get_all() {

    $query = db_select('employees', 'e');

    $query->leftJoin('departments', 'c', 'c.department_id = e.department_id');

    $query->fields('e', ['employee_id','employee_name', 'position', 'department_id']);
    $query->fields('c', ['department_name']);
    
    return $query->execute()->fetchAll() ;
}

function cassiopeia_employees_delete($employee_id) {


  module_invoke_all('employee_deleted', $employee_id);

  db_delete('employees')
    ->condition('employee_id', $employee_id)
    ->execute();

  drupal_goto('quan-ly-nhan-vien');

}


function cassiopeia_employee_form($form, &$form_state, $employee_id = 0) {

  $employee_data = [];

  if ($employee_id) {
    $query = db_select('employees', 'e');
    $query->fields('e');
    $query->leftJoin('departments', 'd', 'd.department_id = e.department_id');
    $query->addField('d', 'department_name');
    $query->condition('e.employee_id', $employee_id);
    $employee_data = $query->execute()->fetchAssoc();
  }

  $form['wrapper'] = [
    '#type' => 'container',
    '#attributes' => ['class' => ['employee-form-wrapper']],
  ];

  $form['wrapper']['employee_id'] = [
      '#type'  => 'hidden',
      '#default_value' => $employee_id ? $employee_data['employee_id'] : 0,
      '#attributes' => [
          'id' => 'edit-employee-id',
          'name' => 'employee_id',
      ],
  ];

  $form['wrapper']['employee_name'] = [
    '#type' => 'textfield',
    '#title' => t('Tên nhân viên'),
    '#required' => TRUE,
    '#default_value' => isset($employee_data['employee_name']) ? $employee_data['employee_name'] : '',
    '#attributes' => [
      'placeholder' => 'Nhập tên nhân viên',
      'id' => 'edit-employee-name'
    ],
    '#prefix' => "<div class='input-wrap'>",
    '#suffix' => "</div>",
  ];

  $form['wrapper']['position'] = [
    '#type' => 'textfield',
    '#title' => t('Chức vụ'),
    '#required' => TRUE,
    '#default_value' => isset($employee_data['position']) ? $employee_data['position'] : '',
    '#attributes' => [
      'placeholder' => 'Nhập chức vụ',
      'id' => 'edit-position'
    ],
    '#prefix' => "<div class='input-wrap'>",
    '#suffix' => "</div>",
  ];

  $options = cassiopeia_departments_get_options();

  $form['wrapper']['department_id'] = [
    '#type' => 'select',
    '#title' => t('Chọn phòng ban'),
    '#options' => $options,
    '#default_value' => isset($employee_data['department_id']) ? $employee_data['department_id'] : '',
    '#attributes' => ['id' => 'edit-employee-department'],
    '#prefix' => "<div class='input-wrap'>",
    '#suffix' => "</div>",
  ];

  $form['wrapper']['submit'] = [
    '#type' => 'submit',
    '#value' => $employee_id ? t('Cập nhật') : t('Thêm mới'),
    '#prefix' => "<div class='form-buttons'>",
    '#suffix' => "</div>",
  ];

  return $form;
}

function cassiopeia_departments_get_options() {
  $options = [];

  $result = db_select('departments', 'd')
    ->fields('d', ['department_id', 'department_name'])
    ->execute();

  foreach ($result as $row) {
    $options[$row->department_id] = $row->department_name;
  }

  return $options;
}

function cassiopeia_employee_form_submit($form, &$form_state){
    $values = $form_state['values'];

    if(!empty($values['employee_id']) && $values['employee_id'] > 0 ){
        db_update('employees')
        ->fields([
            'employee_name' => $values['employee_name'],
            'position' => $values['position'],
            'department_id'=> $values['department_id'],
        ])
        ->condition('employee_id',$values['employee_id'])
        ->execute();
        
        drupal_set_message(t('Cập nhật nhân viên thành công. '));

    

    $employee = [
        'employee_id' => $values['employee_id'],
        'employee_name' => $values['employee_name'],
        'position' => $values['position'],
        'department_id'=> $values['department_id'],
    ];

    module_invoke_all('employee_updated', $employee);

    } else { 
        $employee_id = db_insert('employees')
        ->fields([
            'employee_name' => $values['employee_name'],
            'position' => $values['position'],
            'department_id'=> $values['department_id'],
        ])
        ->execute();
        drupal_set_message(t('Thêm mới nhân viên thành công. '));
    
    $employee = [
        'employee_id' => $employee_id,
        'employee_name' => $values['employee_name'],
        'position' => $values['position'],
        'department_id'=> $values['department_id'],
    ];

    module_invoke_all('employee_add', $employee);
    }

    $form_state['redirect'] = 'quan-ly-nhan-vien';

}


function cassiopeia_employees_department_deleted($department_id){
      db_delete('employees')
    ->condition('department_id', $department_id)
    ->execute();
}
