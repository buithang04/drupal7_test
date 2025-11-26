<?php 


function cassiopeia_classes_list() {

    $classes = cassiopeia_classes_get_all() ;

    return _cassiopeia_render_theme("module","cassiopeia_classes","templates/page-classes.tpl.php", ['classes' => $classes]);

}

function cassiopeia_classes_get_all() {

    $query = db_select('classes', 'c')

        ->fields('c', ['class_id','class_name', 'teacher_name']);

    return $query->execute()->fetchAll() ;
}


function cassiopeia_classes_delete($class_id) {

module_invoke_all('class_deleted', $class_id);


  db_delete('classes')
    ->condition('class_id', $class_id)
    ->execute();
  drupal_goto('quan-ly-lop');

}




function cassiopeia_class_form($form, &$form_state, $class_id = 0) {

  $class_data = [];
if ($class_id) {
  $class_data = db_select('classes', 'c')
    ->fields('c')
    ->condition('class_id', $class_id)
    ->execute()
    ->fetchAssoc();
}


$form['wrapper'] = [
  '#type' => 'container',
  '#attributes' => ['class' => ['class-form-wrapper']],
];


$form['wrapper']['class_id'] = [
  '#type' => 'hidden',
  '#value' => isset($class_data['class_id']) ? $class_data['class_id'] : 0,
];


$form['wrapper']['class_name'] = [
  '#type'         => 'textfield',
  '#title'        => t('Tên lớp (bắt buộc nhập)'),
  '#required'     => TRUE,
  '#default_value'=> isset($class_data['class_name']) ? $class_data['class_name'] : '',
  '#size'         => 60,
  '#maxlength'    => 128,
  '#prefix'       => "<div class='input-wrap'>",
  '#suffix'       => "<p></p></div>",
  '#attributes'   => ['placeholder' => t('Nhập tên lớp')],
];

$form['wrapper']['teacher_name'] = [
  '#type'         => 'textfield',
  '#title'        => t('Tên giáo viên (bắt buộc nhập)'),
  '#required'     => TRUE,
  '#default_value'=> isset($class_data['teacher_name']) ? $class_data['teacher_name'] : '',
  '#size'         => 60,
  '#maxlength'    => 128,
  '#prefix'       => "<div class='input-wrap'>",
  '#suffix'       => "<p></p></div>",
  '#attributes'   => ['placeholder' => t('Nhập tên giáo viên')],
];

$form['wrapper']['submit'] = [
  '#type'       => 'submit',
  '#value'      => $class_id ? t('Cập nhật') : t('Thêm mới'),
  '#prefix'     => "<div class='form-buttons'>",
  '#suffix'     => "</div>",
  '#attributes' => ["class" => ["btn-type-2"]],
];
return $form;

}


function cassiopeia_class_form_submit($form, &$form_state) {
  $values = $form_state['values'];

  if ($values['class_id'] > 0) {
    db_update('classes')
      ->fields([
        'class_name' => $values['class_name'],
        'teacher_name' => $values['teacher_name'],
      ])
      ->condition('class_id', $values['class_id'])
      ->execute();

    drupal_set_message(t('Cập nhật lớp thành công.'));

    $class = [
      'class_id' => $values['class_id'],
      'class_name' => $values['class_name'],
      'teacher_name' => $values['teacher_name'],
    ];

    module_invoke_all('class_updated', $class);

  } else {

    $class_id = db_insert('classes')
      ->fields([
        'class_name' => $values['class_name'],
        'teacher_name' => $values['teacher_name'],
      ])
      ->execute();

    drupal_set_message(t('Thêm mới lớp thành công.'));

    $class = [
      'class_id' => $class_id,
      'class_name' => $values['class_name'],
      'teacher_name' => $values['teacher_name'],
    ];
    
    module_invoke_all('class_added', $class);
  }

  $form_state['redirect'] = 'quan-ly-lop';
}




