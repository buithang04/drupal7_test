<?php
function cassiopeia_classinfo_page($class_id) {
   
    $classinfo = cassiopeia_classinfo_get_by_class($class_id);

    if (empty($classinfo)) {
        return '<p>Lớp không tồn tại.</p>';
    }

 
    return _cassiopeia_render_theme(
        "module",
        "cassiopeia_classinfo",
        "templates/page-classinfo.tpl.php",
        [
            'classinfo' => $classinfo,
            'class_id' => $class_id,
            'class_name' => $classinfo[0]->class_name ?? '',
            'teacher_name' => $classinfo[0]->teacher_name ?? '',
        ]
    );
}


function cassiopeia_classinfo_get_by_class($class_id) {
  $query = db_select('class_full_info', 'cfi')
    ->fields('cfi', [
      'student_id', 'student_name', 'gender', 'birthdate',
      'class_id', 'class_name', 'teacher_name'
    ])
    ->condition('class_id', $class_id)
    ->orderBy('student_id', 'ASC');

  return $query->execute()->fetchAll();
}



function cassiopeia_classinfo_class_deleted($class_id) {
  db_delete('class_full_info')
    ->condition('class_id', $class_id)
    ->execute();
}

function cassiopeia_classinfo_student_deleted($student_id) {
  db_delete('class_full_info')
    ->condition('student_id', $student_id)
    ->execute();
}

function cassiopeia_classinfo_class_added($class) {

  db_insert('class_full_info')
    ->fields([
      'class_id' => $class['class_id'],
      'class_name' => $class['class_name'],
      'teacher_name' => $class['teacher_name'],
      'student_id' => NULL,
      'student_name' => NULL,
      'gender' => NULL,
      'birthdate' => NULL,
      'created_at' => date('Y-m-d H:i:s'),
    ])
    ->execute();
}

function cassiopeia_classinfo_student_added($student) {
 
  $class = db_select('classes', 'c')
    ->fields('c', ['class_name', 'teacher_name'])
    ->condition('class_id', $student['class_id'])
    ->execute()
    ->fetchAssoc();

  $class_name   = $class['class_name'] ?? '';
  $teacher_name = $class['teacher_name'] ?? '';

  db_insert('class_full_info')
    ->fields([
      'class_id'     => $student['class_id'],
      'class_name'   => $class_name,    
      'teacher_name' => $teacher_name, 
      'student_id'   => $student['student_id'],
      'student_name' => $student['student_name'],
      'gender'       => $student['gender'],
      'birthdate'    => $student['birthdate'],
      'created_at'   => date('Y-m-d H:i:s'),
    ])
    ->execute();
}

function cassiopeia_classinfo_class_updated($class) {
  db_update('class_full_info')
    ->fields([
      'class_name' => $class['class_name'],
      'teacher_name' => $class['teacher_name'],
    ])
    ->condition('class_id', $class['class_id'])
    ->execute();
}
function cassiopeia_classinfo_student_updated($student) {
  db_update('class_full_info')
    ->fields([
      'student_name' => $student['student_name'],
      'gender' => $student['gender'],
      'birthdate' => $student['birthdate'],
      'class_id' => $student['class_id'], 
    ])
    ->condition('student_id', $student['student_id'])
    ->execute();
}


