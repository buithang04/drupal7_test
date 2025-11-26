


<div class="classes-wrapper">
  <h1>Danh sách lớp</h1>
  <br>
  <button type="button" class="btn-green bnt-add-class12">
                <span class="fa fa-plus"></span>
                Thêm mới lớp
            </button>
  <br>
  <table class="classes-table">
    <thead>
      <tr>
        <th>STT</th>
        <th>Tên lớp</th>
        <th>Giáo viên</th>
        <th>Actions</th>
      </tr>
    </thead>
    <tbody>
      <?php 
      $stt = 1;
      if (!empty($classes) && is_array($classes)):
          foreach ($classes as $class): 
      ?>
      <tr>
        <td><?php echo $stt++; ?></td>
        <td><a href="<?php echo url('thong-tin-lop/' . $class->class_id); ?>"><?php echo $class->class_name; ?></td></a>
        <td><?php echo $class->teacher_name; ?></td>
        <td>
          <button type="button"  class="btn-edit-classes" onclick="window.location.href='/classes/edit/<?php echo $class->class_id; ?>'"><i class="far fa-pen-to-square fa-fw"></i></button>
          <button type="button" class="btn-delete-classes" data-id="<?php echo $class->class_id; ?>" data-name="<?php echo htmlspecialchars($class->class_name); ?>" title="Xóa lớp"><i class="far fa-trash-can fa-fw"></i></button>
        </td>
      </tr>

      <?php 
          endforeach; 
      else: 
      ?>
      <tr>
        <td colspan="4">Không có lớp nào.</td>
      </tr>
      <?php endif; ?>
    </tbody>
  </table>
</div>



  <div id="addclass" class="modal fade" role="dialog">
    <div class="modal-dialog">
        <!-- Modal content-->
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal">&times;</button>
                <h4 class="modal-title">T</h4>
            </div>
            <div class="modal-body">
                <?php
                $cassiopeia_class_form = drupal_get_form("cassiopeia_class_form");
                if(!empty($cassiopeia_class_form)){
                    $cassiopeia_class_form = drupal_render($cassiopeia_class_form);
                    print($cassiopeia_class_form);
                }
                ?>
            </div>
        </div>

    </div>
</div>