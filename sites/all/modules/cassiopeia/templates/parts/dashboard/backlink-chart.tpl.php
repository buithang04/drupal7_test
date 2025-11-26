<?php

global $user;

if(empty($user->uid)){
//    drupal_goto("/index.html");
}

$cache = array();
$cache['from_date'] = date("d-m-Y",strtotime(date("d-m-Y",REQUEST_TIME)." - 14 days"));
$cache['to_date'] = date("d-m-Y",REQUEST_TIME);
$conditions = array();
$conditions['status'] = array(
    "type"      => "propertyCondition",
    "value"     => 1,
    "condition" => "=",
);
$conditions['changed'] = array(
    "type"      => "propertyOrderBy",
    "direction" => "DESC",
);
$conditions['uid'] = array(
    "type"      => "propertyCondition",
    "value"     => $user->uid,
    "condition" => "="
);
$conditions['nid'] = array(
    "type"      => "propertyCondition",
    "value"     => $pid,
    "condition" => "="
);
$totalBacklinks = cassiopeia_get_items_by_conditions($conditions,"project_backlink","node");
$conditions['range'] = array(
    "type"      => "range",
    "start"     => 0,
    "limit"     => 5,
);
$project_backlinks = cassiopeia_get_items_by_conditions($conditions,"project_backlink","node");
//_print_r($project_backlinks)
$maxNumber = 0;
$dataBacklinks = array();
$TotalBacklink = 0;
$ProjectBanklink = array();
$ValueX = array();
$FromDateTimestamp = strtotime($cache['from_date']);
$ToDateTimestamp = strtotime($cache['to_date']);
if(!empty($project_backlinks)){
    foreach($project_backlinks as $project_backlink){
        $dataBackLink = array();
        $TotalBanklinkByProject = 0;
        $cache['project'] = $project_backlink;
        $_backlinks = cassiopeia_get_backlink_project_report($cache);
        $domains = cassiopeia_get_backlink_domain_report($cache);

        $backLinkList = array();
        $query = db_select("tbl_backlink_report","tbl_backlink_report");
        $query->fields("tbl_backlink_report");
        $query->condition("tbl_backlink_report.nid",$project_backlink->nid);
        $query->orderBy("tbl_backlink_report.date","DESC");
        $query->range(0,1);
        $last_report = $query->execute()->fetchObject();
//        _print_r($last_report);
        $query = db_select("tbl_backlink_report","tbl_backlink_report");
        $query->fields("tbl_backlink_report");
        $query->condition("tbl_backlink_report.nid",$project_backlink->nid);
        $query->condition("tbl_backlink_report.date",array(strtotime(date("01-m-Y 00:00:00",strtotime($cache['from_date']))),strtotime(date("t-m-Y 23:59:59",strtotime($cache['to_date'])))),"BETWEEN");
        $report = $query->execute()->fetchAll();
        $reportList = [];
        if(!empty($report)){
            foreach($report as $item){
                $reportList[$item->date] = $item;
            }
        }
        $lastValue = !empty($last_report)?$last_report->domain_count:0;
        $temp = 0;
//        print_r($last_report);
        if(!empty($last_report)){
            if($FromDateTimestamp>$last_report->date){
                $temp = $lastValue;
            }
        }else{
            $query = db_select("tbl_backlink","tbl_backlink");
            $query->fields("tbl_backlink");
            $query->join("tbl_backlink_detail","tbl_backlink_detail","tbl_backlink.id=tbl_backlink_detail.nid");
            $query->addExpression("COUNT(tbl_backlink_detail.id)","TotalBacklink");
            $query->condition("tbl_backlink.pid",$project_backlink->nid);
            $__backlinkResult = $query->execute()->fetchObject();
            $query = db_select("tbl_backlink","tbl_backlink");
            $query->fields("tbl_backlink");
            $query->addField("tbl_backlink","id","bid");
            $query->condition("tbl_backlink.pid",$project_backlink->nid);
            $query->groupBy("domain");
            $__domains = $query->execute()->fetchAll();
            try{
                db_insert("tbl_backlink_report")->fields(array(
                    "created"   => REQUEST_TIME,
                    "date"   => strtotime(date("d-m-Y 00:00:00",REQUEST_TIME)),
                    "backlink_count"    => $__backlinkResult->TotalBacklink,
                    "domain_count"    => count($__domains),
                    "nid"    => $project_backlink->nid,
                ))->execute();
                $query = db_select("tbl_backlink_report","tbl_backlink_report");
                $query->fields("tbl_backlink_report");
                $query->condition("tbl_backlink_report.nid",$project_backlink->nid);
                $query->orderBy("tbl_backlink_report.date","DESC");
                $query->range(0,1);
                $last_report = $query->execute()->fetchObject();
                if($FromDateTimestamp>$last_report->date){
                    $temp = $lastValue;
                }
                $query = db_select("tbl_backlink_report","tbl_backlink_report");
                $query->fields("tbl_backlink_report");
                $query->condition("tbl_backlink_report.nid",$project_backlink->nid);
                $query->condition("tbl_backlink_report.date",array(strtotime(date("01-m-Y 00:00:00",strtotime($cache['from_date']))),strtotime(date("t-m-Y 23:59:59",strtotime($cache['to_date'])))),"BETWEEN");
                $report = $query->execute()->fetchAll();
                $reportList = [];
                if(!empty($report)){
                    foreach($report as $item){
                        $reportList[$item->date] = $item;
                    }
                }
            }catch (Exception $e){

            }
        }
//        _print_r($temp);
        for($i=$FromDateTimestamp;$i<=$ToDateTimestamp;$i+=86400){
            if(empty($temp)){
                $temp = !empty($reportList[$i])?$reportList[$i]->domain_count:0;
            }
            $current = !empty($reportList[$i])?$reportList[$i]->domain_count:$temp;
            $TotalBacklink+=$current;
            $TotalBanklinkByProject=$current;
            $maxNumber = $maxNumber<$current?$current:$maxNumber;

            array_push($dataBackLink,$current);
        }
        $ProjectBanklink[$project_backlink->nid]['BanklinkCount'] = $TotalBanklinkByProject;
        $ProjectBanklink[$project_backlink->nid]['Project'] = $project_backlink;
        $ProjectTitle = $project_backlink->title;
        $P = vn_to_str($ProjectTitle);
//        $StrLen = strlen($P);
//        if($StrLen>10){
//            $temp = strrev($ProjectTitle);
//            $temp = substr($temp,$StrLen-10);
//            $ProjectTitle = strrev($temp)."...";
//        }
        $dataBacklinks[] = array(
            "title" => $ProjectTitle,
            "value" => $dataBackLink,
            "alt"   => $project_backlink->title,
        );
    }
}
//_print_r($dataBacklinks);
for($i=$FromDateTimestamp;$i<=$ToDateTimestamp;$i+=86400){
    array_push($ValueX,date('d/m',$i));
}
$maxNumber = $maxNumber==0?1000:$maxNumber;
$DisplayLegend = true;

//print_r($dataBacklinks);
if(empty($dataBacklinks)){
    $DisplayLegend = false;
}
$dataBacklinks = !empty($dataBacklinks)?$dataBacklinks:array(0=>array());
//$dataBacklinks = array_reverse($dataBacklinks);
//$ProjectBanklink = array_reverse($ProjectBanklink);
//print_r($dataBacklinks);
$colorList = array(
    1 => "#1f9f4c",
    2 => "#f8a03b",
    3 => "#0084ff",
    4 => "#ef9ac4",
    5 => "#f8de66",
);

?>
<input hidden type="text" value='<?php echo json_encode($ValueX); ?>' id="ValueX">
<input hidden type="text" id="dataProjectBanklink" value='<?php echo json_encode($dataBacklinks); ?>' display-legend="<?php echo $DisplayLegend; ?>">
<input hidden type="text" id="maxBacklink" value='<?php echo $maxNumber; ?>'>

<canvas id="back_link_chart" style="width:100%;height: 100%;"></canvas>

<script>
    (function($) {
        var colorArray = ["#F9AA4D"];
        let displayLegend = jQuery("#dataProjectBanklink").attr("display-legend");
        let maxNumber = jQuery("#maxBacklink").val();
        if (maxNumber < 1) {
            return false;
        }
        let xValues = jQuery("#ValueX").val();
        let dataProjectBanklink = JSON.parse(jQuery("#dataProjectBanklink").val());
        console.log("dataProjectBanklink",dataProjectBanklink);
        let dataSet = [];
        let stt = 0;
        $.each(dataProjectBanklink, function(index, value) {
            let _data = {};
            _data['alt'] = value.alt;
            _data['label'] = value.title;
            _data['data'] = value.value;
            _data['backgroundColor'] = colorArray[stt];
            _data['fill'] = false;
            _data['borderColor'] = colorArray[stt];
            dataSet.push(_data);
            stt++;
        });
        new Chart("back_link_chart", {
            type: "line",
            data: {
                labels: JSON.parse(xValues),
                datasets: dataSet
            },
            options: {
                scales: {
                    y: {
                        min: 0,
                        max: parseInt(maxNumber),
                    }
                },
                plugins: {
                    legend: {
                        display: false,
                        position: 'bottom',
                        align: 'start',
                        maxWidth: 10,
                        labels: {
                            padding: 20,
                            // boxWidth : 20
                        },
                        onHover: function(context) {
                            console.log("alt", context);
                        }
                    },
                    // tooltip: {
                    //     callbacks: {
                    //         label: function(context) {
                    //             let label = context.dataset.alt || '';
                    //
                    //             // label = "nwe la";
                    //             return label;
                    //         }
                    //     }
                    // }
                }
            }
        });
    })(jQuery);
</script>