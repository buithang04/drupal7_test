<?php 


function cassiopeia_departments_list() {

    $departments = cassiopeia_departments_get_all() ;

    return _cassiopeia_render_theme("module","cassiopeia_departments","templates/page-departments.tpl.php", ['departments' => $departments]);

}

function cassiopeia_departments_get_all() {

    $query = db_select('departments', 'c')

        ->fields('c', ['department_id','department_name', 'department_desc']);

    return $query->execute()->fetchAll() ;
}


function cassiopeia_departments_delete($department_id) {

module_invoke_all('department_delete', $department_id);


  db_delete('departments')
    ->condition('department_id', $department_id)
    ->execute();
  drupal_goto('quan-ly-phong-ban');

}




function cassiopeia_department_form($form, &$form_state, $department_id = 0) {

  $department_data = [];

  if ($department_id) {
    $department_data = db_select('departments', 'd')
      ->fields('d')
      ->condition('department_id', $department_id)
      ->execute()
      ->fetchAssoc();
  }

  $form['wrapper'] = [
    '#type' => 'container',
    '#attributes' => ['class' => ['department-form-wrapper']],
  ];

  
  $form['wrapper']['department_id'] = [
  '#type' => 'hidden',
  '#default_value' => 0, 
  '#attributes' => ['id' => 'edit-department-id'],
  ];

  $form['wrapper']['department_name'] = [
    '#type' => 'textfield',
    '#title' => t('Tên phòng ban (bắt buộc nhập)'),
    '#required' => TRUE,
    '#default_value' => isset($department_data['department_name']) ? $department_data['department_name'] : '',
    '#size' => 60,
    '#maxlength' => 100,
    '#prefix' => "<div class='input-wrap'>",
    '#suffix' => "<p></p></div>",
    '#attributes' => ['id' => 'edit-department-name', 'placeholder' => t('Nhập tên phòng ban')],
  ];
  $form['wrapper']['department_desc'] = [
    '#type' => 'textfield',
    '#title' => t('Mô tả phòng ban (bắt buộc nhập)'),
    '#required' => TRUE,
    '#default_value' => isset($department_data['department_desc']) ? $department_data['department_desc'] : '',
    '#size' => 60,
    '#maxlength' => 255,
    '#prefix' => "<div class='input-wrap'>",
    '#suffix' => "<p></p></div>",
    '#attributes' => ['id' => 'edit-department-desc', 'placeholder' => t('Nhập mô tả phòng ban')],
  ];

  $form['wrapper']['submit'] = [
    '#type' => 'submit',
    '#value' => $department_id ? t('Cập nhật') : t('Thêm mới'),
    '#prefix' => "<div class='form-buttons'>",
    '#suffix' => "</div>",
    '#attributes' => ["class" => ["btn-type-2"]],
  ];

  return $form;
}


function cassiopeia_department_form_submit($form, &$form_state) {
  $values = $form_state['values'];

 if (!empty($values['department_id']) && $values['department_id'] > 0) {

    db_update('departments')
      ->fields([
          'department_name' => $values['department_name'],
          'department_desc' => $values['department_desc'],
      ])
      ->condition('department_id', $values['department_id'])
      ->execute();

    drupal_set_message(t('Cập nhật phòng ban thành công.'));

    $department = [
      'department_id' => $values['department_id'],
      'department_name' => $values['department_name'],
      'department_desc' => $values['department_desc'],
    ];

    module_invoke_all('department_updated', $department);

  } else {

    $department_id = db_insert('departments')
      ->fields([
        'department_name' => $values['department_name'],
        'department_desc' => $values['department_desc'],
      ])
      ->execute();

    drupal_set_message(t('Thêm mới phòng ban thành công.'));

    $department = [
      'department_id' => $department_id,
      'department_name' => $values['department_name'],
      'department_desc' => $values['department_desc'],
    ];
    
    module_invoke_all('department_added', $department);
  }

  $form_state['redirect'] = 'quan-ly-phong-ban';
}




