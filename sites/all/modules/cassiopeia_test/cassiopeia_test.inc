<?php
function cassiopeia_test_run() {
    // exit();

  cassiopeia_test_update_test(3, array('title' => 'abc'));


  drupal_set_message("Hook test_update đã chạy");

  return "aaaaaaaaaaaaaa";
}

function cassiopeia_test_create($data) {
  $data['created'] = REQUEST_TIME;

  $id = db_insert('test')
    ->fields($data)
    ->execute();

  module_invoke_all('test_insert', $id, $data);

  return $id;
}

function cassiopeia_test_load($id) {
  return db_select('test', 't')
    ->fields('t')
    ->condition('id', $id)
    ->execute()
    ->fetchAssoc();
}


function cassiopeia_test_update_test($id, $data) {
  $data['updated'] = REQUEST_TIME;

  db_update('test')
    ->fields($data)
    ->condition('id', $id)
    ->execute();

  module_invoke_all('test_update', $id, $data);
}


function cassiopeia_test_delete_test($id) {
  db_delete('test')
    ->condition('id', $id)
    ->execute();

  module_invoke_all('test_delete', $id);
}


function cassiopeia_test_insert($id, $data) {
  watchdog('cassiopeia_test', 'Inserted test record: @id', array('@id' => $id));
}

function cassiopeia_test_update($id, $data) {
   db_update('test')
    ->fields($data)
    ->condition('id', $id+1)
    ->execute();
}


function cassiopeia_test_delete($id) {
  watchdog('cassiopeia_test', 'Delete test record: @id', array('@id' => $id));
}


function cassiopeia_test_form2($form, &$form_state) {

$form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => TRUE,
  );

  $form['subtitle'] = array(
    '#type' => 'textfield',
    '#title' => t('Subtitle'),
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
  );

  $form['quantity'] = array(
    '#type' => 'number',
    '#title' => t('Quantity'),
    '#default_value' => 0,
  );

  $form['price'] = array(
    '#type' => 'textfield',
    '#title' => t('Price'),
    '#default_value' => 0,
  );

  $form['is_active'] = array(
    '#type' => 'checkbox',
    '#title' => t('Active'),
    '#default_value' => 1,
  );

  $form['note'] = array(
    '#type' => 'textfield',
    '#title' => t('Note'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
 $form['#theme'] = array('cassiopeia_test_form_theme');
 
  return $form;
}