<?php
drupal_add_css(drupal_get_path('module', 'cassiopeia_reports') . '/css/reports.css');
drupal_add_js(drupal_get_path('module', 'cassiopeia_reports') . '/js/report-table.js');
?>

<div class="report-container">


  <div class="filter-box">
    <input type="text" id="search" placeholder="Tìm phòng ban..." class="search-input">
  </div>

  <div class="filter-letters">

    <?php foreach (range('A','Z') as $char): ?>
      <button class="filter-letter" data-letter="<?php print $char; ?>">
        <?php print $char; ?>
      </button>
    <?php endforeach; ?>

    <button class="filter-letter filter-all" data-letter="all">
      Tất cả
    </button>

  </div>

  <!-- Bảng báo cáo DỰ ÁN -->
  <table class="table-report" id="reportTable">
    
      <tr>
        <th>STT</th>

        <th class="sort" data-sort="department" data-direction="ASC">
          Phòng ban
        </th>

        <th class="sort" data-sort="count" data-direction="ASC">
          Số dự án
        </th>
      </tr>
    

    
      <?php $i = 1; ?>
      <?php foreach ($records as $row): ?>
        <tr>

          <td class="stt"><?php print $i++; ?></td>

          <td class="department" data-department="<?php print $row->department_name; ?>">
            <?php print $row->department_name; ?>
          </td>

          <td class="count" data-count="<?php print $row->total_tasks; ?>">
            <?php print $row->total_tasks; ?>
          </td>

        </tr>
      <?php endforeach; ?>
  

</div>
