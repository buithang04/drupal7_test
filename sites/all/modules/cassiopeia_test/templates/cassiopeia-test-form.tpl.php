<div class="cassiopeia-test-form-wrapper">

  <div class="form-item">
    <?php print render($form['title']); ?>
  </div>

  <div class="form-item">
    <?php print render($form['subtitle']); ?>
  </div>

  <div class="form-item">
    <?php print render($form['description']); ?>
  </div>

  <div class="form-item-inline">
    <?php print render($form['quantity']); ?>
    <?php print render($form['price']); ?>
  </div>

  <div class="form-item">
    <?php print render($form['is_active']); ?>
  </div>

  <div class="form-item">
    <?php print render($form['note']); ?>
  </div>

  <div class="form-actions" >
    <?php print render($form['submit']); ?>
  </div>

  <?php print drupal_render_children($form); ?>
</div>
