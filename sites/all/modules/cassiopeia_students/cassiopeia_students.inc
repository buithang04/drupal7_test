<?php 


function cassiopeia_students_list() {

    $students = cassiopeia_students_get_all() ;

    return _cassiopeia_render_theme("module","cassiopeia_students","templates/page-students.tpl.php", ['students' => $students]);

}

function cassiopeia_students_get_all() {
  $query = db_select('students', 's');

  $query->leftJoin('classes', 'c', 'c.class_id = s.class_id');

  $query->fields('s', ['student_id', 'student_name', 'gender', 'birthdate', 'class_id']);
  $query->fields('c', ['class_name']);

  return $query->execute()->fetchAll();
}



function cassiopeia_students_delete($student_id) {


  module_invoke_all('student_deleted', $student_id);

  db_delete('students')
    ->condition('student_id', $student_id)
    ->execute();

  drupal_goto('quan-ly-sinhvien');



}


function cassiopeia_students_class_deleted($class_id) {
  
  $students = db_select('students', 's')
    ->fields('s', ['student_id'])
    ->condition('class_id', $class_id)
    ->execute()
    ->fetchCol();

  foreach ($students as $sid) {

    db_delete('students')
      ->condition('student_id', $sid)
      ->execute();

    module_invoke_all('student_deleted', $sid);
  }
}



function cassiopeia_student_form($form, &$form_state, $student_id = 0) {

  $student_data = [];

  if ($student_id) {
    $query = db_select('students', 's');
    $query->fields('s');
    $query->leftJoin('classes', 'c', 'c.class_id = s.class_id');
    $query->addField('c', 'class_name');
    $query->condition('s.student_id', $student_id);
    $student_data = $query->execute()->fetchAssoc();
  }

  $form['wrapper'] = [
    '#type' => 'container',
    '#attributes' => ['class' => ['student-form-wrapper']],
  ];

  $form['wrapper']['student_id'] = [
      '#type'  => 'hidden',
      '#default_value' => $student_id ? $student_data['student_id'] : 0,
      '#attributes' => [
          'id' => 'edit-student-id',
          'name' => 'student_id',
      ],
  ];

  $form['wrapper']['student_name'] = [
    '#type' => 'textfield',
    '#title' => t('Tên sinh viên'),
    '#required' => TRUE,
    '#default_value' => isset($student_data['student_name']) ? $student_data['student_name'] : '',
    '#attributes' => [
      'placeholder' => 'Nhập tên sinh viên',
      'id' => 'edit-student-name'
    ],
    '#prefix' => "<div class='input-wrap'>",
    '#suffix' => "</div>",
  ];

  $form['wrapper']['gender'] = [
    '#type' => 'select',
    '#title' => t('Giới tính'),
    '#options' => [
      'Nam' => 'Nam',
      'Nữ' => 'Nữ'
    ],
    '#default_value' => isset($student_data['gender']) ? $student_data['gender'] : '',
    '#attributes' => ['id' => 'edit-gender'],
    '#prefix' => "<div class='input-wrap'>",
    '#suffix' => "</div>",
  ];

  $form['wrapper']['birthdate'] = [
    '#type' => 'date',
    '#title' => 'Ngày sinh',
    '#default_value' => !empty($student_data['birthdate'])
      ? date('Y-m-d', strtotime($student_data['birthdate']))
      : NULL, 
    '#attributes' => [
    'placeholder' => 'dd-mm-yyyy',
    'id' => 'edit-birthdate'],
    '#prefix' => "<div class='input-wrap'>",
    '#suffix' => "</div>",
  ];

  $options = cassiopeia_classes_get_options();

  $form['wrapper']['class_id'] = [
    '#type' => 'select',
    '#title' => t('Chọn lớp'),
    '#options' => $options,
    '#default_value' => isset($student_data['class_id']) ? $student_data['class_id'] : '',
    '#attributes' => ['id' => 'edit-class-id'],
    '#prefix' => "<div class='input-wrap'>",
    '#suffix' => "</div>",
  ];

  $form['wrapper']['submit'] = [
    '#type' => 'submit',
    '#value' => $student_id ? t('Cập nhật') : t('Thêm mới'),
    '#prefix' => "<div class='form-buttons'>",
    '#suffix' => "</div>",
  ];
  

  return $form;
}


function cassiopeia_classes_get_options() {
  $options = [];

  $result = db_select('classes', 'c')
    ->fields('c', ['class_id', 'class_name'])
    ->execute();

  foreach ($result as $row) {
    $options[$row->class_id] = $row->class_name;
  }

  return $options;
}


function cassiopeia_student_form_submit($form, &$form_state) {
  $values = $form_state['values'];

  if (is_array($values['birthdate'])) {
    $birthdate = sprintf(
      '%04d-%02d-%02d',
      $values['birthdate']['year'],
      $values['birthdate']['month'],
      $values['birthdate']['day']
    );
  }
  else {
    $birthdate = $values['birthdate'];
  }

  $data = [
    'student_name' => $values['student_name'],
    'gender'       => $values['gender'],
    'birthdate'    => $birthdate,
    'class_id'     => $values['class_id'],
  ];

  $class = db_select('classes', 'c')
    ->fields('c', ['class_name', 'teacher_name'])
    ->condition('class_id', $values['class_id'])
    ->execute()
    ->fetchAssoc();

  $class_name   = $class['class_name'] ?? '';
  $teacher_name = $class['teacher_name'] ?? '';

  if (!empty($values['student_id']) && $values['student_id'] > 0) {
 
    db_update('students')
      ->fields($data)
      ->condition('student_id', $values['student_id'])
      ->execute();

    drupal_set_message(t('Cập nhật sinh viên thành công.'));

    $student = [
      'student_id'   => $values['student_id'],
      'student_name' => $values['student_name'],
      'gender'       => $values['gender'],
      'birthdate'    => $birthdate,
      'class_id'     => $values['class_id'],
      'class_name'   => $class_name,
      'teacher_name' => $teacher_name,
    ];

    module_invoke_all('student_updated', $student);

  } else {
    $student_id = db_insert('students')
      ->fields($data)
      ->execute();

    drupal_set_message(t('Thêm mới sinh viên thành công.'));

    $student = [
      'student_id'   => $student_id,
      'student_name' => $values['student_name'],
      'gender'       => $values['gender'],
      'birthdate'    => $birthdate,
      'class_id'     => $values['class_id'],
      'class_name'   => $class_name,
      'teacher_name' => $teacher_name,
    ];

    module_invoke_all('student_added', $student);
  }

  $form_state['redirect'] = 'quan-ly-sinhvien';
}






