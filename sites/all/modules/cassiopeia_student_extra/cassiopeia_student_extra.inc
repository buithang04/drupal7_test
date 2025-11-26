<?php
function cassiopeia_student_extra_list($student_id) {
  if (!$student_id) {
    drupal_set_message(t('Không có sinh viên.'), 'error');
    return;
  }
  $extra = db_select('student_extra', 'e')
    ->fields('e')
    ->condition('student_id', $student_id)
    ->execute()
    ->fetchAssoc();

  $student = db_select('students', 's')
    ->fields('s', ['student_name'])
    ->condition('student_id', $student_id)
    ->execute()
    ->fetchAssoc();

  $extra['student_name'] = $student['student_name'] ?? '';

  return _cassiopeia_render_theme(
    "module",
    "cassiopeia_student_extra",
    "templates/page-student-extra.tpl.php",
    [
      'extra' => $extra,
    ]
  );
}

function cassiopeia_student_extra_form($form, &$form_state, $student_id = 0) {
  if (!$student_id) {
    drupal_set_message(t('Không có sinh viên để chỉnh sửa.'), 'error');
    return [];
  }

  $extra = db_select('student_extra', 'e')
    ->fields('e')
    ->condition('student_id', $student_id)
    ->execute()
    ->fetchAssoc();

  $form['wrapper'] = ['#type'=>'container','#attributes'=>['class'=>['student-extra-form-wrapper']]];

  $form['wrapper']['student_id'] = [
    '#type' => 'hidden',
    '#default_value' => $student_id,
  ];

  $form['wrapper']['phone'] = [
    '#type'=>'textfield',
    '#title'=>t('Số điện thoại'),
    '#default_value'=>$extra['phone']??'',
    '#attributes'=>['placeholder'=>'Nhập số điện thoại'],
  ];

  $form['wrapper']['email'] = [
    '#type'=>'textfield',
    '#title'=>t('Email'),
    '#default_value'=>$extra['email']??'',
    '#attributes'=>['placeholder'=>'Nhập email'],
  ];

    $form['wrapper']['address'] = [
      '#type'=>'textfield',
      '#title'=>t('Địa chỉ'),
      '#default_value'=>$extra['address']??'',
      '#attributes'=>['placeholder'=>'Nhập địa chỉ'],
    ];

$form['wrapper']['avatar'] = [
  '#type' => 'managed_file',
  '#title' => t('Avatar'),
  '#upload_location' => 'public://student_avatars/',
  '#upload_validators' => [
    'file_validate_extensions' => ['png jpg jpeg gif'],
    'file_validate_size' => [5 * 1024 * 1024 * 10 ],
  ],
 '#default_value' => !empty($extra['avatar_fid']) ? (int)$extra['avatar_fid'] : NULL,

];
$form['wrapper']['father_name'] = [
  '#type'=>'textfield',
  '#title'=>t('Tên cha'),
  '#default_value'=>$extra['father_name']??'',
  '#attributes'=>['placeholder'=>'Nhập tên cha'],
];

$form['wrapper']['father_phone'] = [
  '#type'=>'textfield',
  '#title'=>t('SĐT cha'),
  '#default_value'=>$extra['father_phone']??'',
  '#attributes'=>['placeholder'=>'Nhập SĐT cha'],
];

$form['wrapper']['mother_name'] = [
  '#type'=>'textfield',
  '#title'=>t('Tên mẹ'),
  '#default_value'=>$extra['mother_name']??'',
  '#attributes'=>['placeholder'=>'Nhập tên mẹ'],
];

$form['wrapper']['mother_phone'] = [
  '#type'=>'textfield',
  '#title'=>t('SĐT mẹ'),
  '#default_value'=>$extra['mother_phone']??'',
  '#attributes'=>['placeholder'=>'Nhập SĐT mẹ'],
];

  $form['wrapper']['submit'] = [
    '#type'=>'submit',
    '#value'=>t('Cập nhật'),
    '#prefix'=>"<div class='form-buttons'>",
    '#suffix'=>"</div>",
  ];

  return $form;
}
function cassiopeia_student_extra_form_submit($form, &$form_state) {
  $v = $form_state['values'];
  $avatar_fid = NULL;

  if (!empty($v['avatar'])) {
    $fid = (int) $v['avatar'];
    $file = file_load($fid);

    if ($file && !empty($file->uri)) {
      $file->status = FILE_STATUS_PERMANENT;
      file_save($file);
      file_usage_add($file, 'cassiopeia_student_extra', 'student_extra', $v['student_id']);
      $avatar_fid = $fid;
    }
  }
  db_update('student_extra')
    ->fields([
      'phone' => $v['phone'],
      'email' => $v['email'],
      'address' => $v['address'],
      'avatar_fid' => $avatar_fid,
      'father_name' => $v['father_name'],
      'father_phone' => $v['father_phone'],
      'mother_name' => $v['mother_name'],
      'mother_phone' => $v['mother_phone'],
      'changed' => REQUEST_TIME,
    ])
    ->condition('student_id', $v['student_id'])
    ->execute();

  drupal_set_message(t('Cập nhật thông tin cá nhân thành công.'));

  $form_state['redirect'] = 'thong-tin-ca-nhan/' . $v['student_id'];
}




function cassiopeia_student_extra_student_added($student) {
  db_insert('student_extra')
    ->fields([
      'student_id' => $student['student_id'],
      'phone' => NULL,
      'email' => NULL,
      'address' => NULL,
      'avatar_fid' => NULL,
      'father_name' => NULL,
      'father_phone' => NULL,
      'mother_name' => NULL,
      'mother_phone' => NULL,
      'created' => REQUEST_TIME,
      'changed' => REQUEST_TIME,
    ])
    ->execute();
}


function cassiopeia_student_extra_student_deleted($student_id) {
  db_delete('student_extra')
    ->condition('student_id', $student_id)
    ->execute();
}
