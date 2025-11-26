// var colorArray = {};
// colorArray[0] = "#1f9f4c";
// colorArray.push("#1f9f4c");
// console.log("colorArray", colorArray);
(function($) {
    function cassiopeiaGetKeywordChart(){
        let pid = $("input[name='keywords']:checked").val();
        $.ajax({
            method: "POST",
            url: "/cassiopeia/ajax",
            data: {
                cmd: "getKeywordChartDashboard",
                pid: pid
            },
            success: function (result) {
                $(".keyword-chart-result").html(result.html);
            }
        });
    }
    function cassiopeiaGetBacklinkChart(){
        let pid = $("input[name='domain']:checked").val();
        $.ajax({
            method: "POST",
            url: "/cassiopeia/ajax",
            data: {
                cmd: "getBacklinkChartDashboard",
                pid: pid
            },
            success: function (result) {
                $(".backlink-chart-result").html(result.html);
            }
        });
    }
    function cassiopeiaCreateBacklinkChart() {
        var colorArray = ["#FDDFBC"];
        let displayLegend = jQuery("#dataProjectBanklink").attr("display-legend");
        let maxNumber = jQuery("#maxBacklink").val();
        if (maxNumber < 1) {
            return false;
        }
        let xValues = jQuery("#ValueX").val();
        let dataProjectBanklink = JSON.parse(jQuery("#dataProjectBanklink").val());
        let dataSet = [];
        let stt = 0;
        $.each(dataProjectBanklink, function(index, value) {
            let _data = {};
            _data['alt'] = value.alt;
            _data['label'] = value.title;
            _data['data'] = value.value;
            _data['backgroundColor'] = colorArray[stt];
            _data['fill'] = true;
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
    }

    function cassiopeiaCreateKeywordChart() {
        var colorArray = ["#F3F9FF"];
        let displayLegend = jQuery("#dataProjectKeyword").attr("display-legend");
        let maxNumber = jQuery("#maxKeyword").val();
        let xValues = jQuery("#keywordX").val();
        let dataProjectBanklink = JSON.parse(jQuery("#dataProjectKeyword").val());
        if (JSON.parse(xValues).length < 1) {
            return false;
        }
        let dataSet = [];
        let stt = 0;
        $.each(dataProjectBanklink, function(index, value) {
            let _data = {};
            _data['label'] = value.title;
            _data['data'] = value.value;
            _data['backgroundColor'] = colorArray[stt];
            _data['fill'] = "end";
            _data['borderColor'] = colorArray[stt];
            dataSet.push(_data);
            stt++;
            console.log("_data", _data);
        });
        // }

        // return;
        // let dataDomain = jQuery("#dataDomain").val();
        new Chart("keyword_chart", {
            type: "line",
            data: {
                labels: JSON.parse(xValues),
                datasets: dataSet,
            },
            options: {
                // legend: { display: false },
                scales: {
                    y: {
                        reverse: true,
                        min: 0,
                        max: parseInt(maxNumber),
                    },
                },
                plugins: {
                    legend: {
                        display: false,
                        // maxWidth: 5,
                        position: 'bottom',
                        align: 'start',
                        labels: {
                            padding: 20
                        },
                    }
                }
            }
        });
    }
    $("document").ready(function(e) {
        cassiopeiaGetKeywordChart();
        cassiopeiaGetBacklinkChart();
        $("input[name='domain']").change(function (e) {
            cassiopeiaGetBacklinkChart();
        });
        $("input[name='keywords']").change(function (e) {
            cassiopeiaGetKeywordChart();
        });
        var result = $(".home-backlinks tbody tr").sort(function(a, b) {
            var contentA = $(a).find("td[data-key='title'] a").text();
            var contentB = $(b).find("td[data-key='title'] a").text();
            return (contentA < contentB) ? -1 : (contentA > contentB) ? 1 : 0;
        });
        $(".home-backlinks .home-backlinks table tbody").html(result);
        $(".home-page .home-backlinks .sort").click(function(e) {
            let _this = $(this);
            // $(".home-page .home-backlinks .sort").removeClass("current");
            // _this.addClass("current");
            let direction = _this.attr("data-direction");
            let sort = _this.attr("data-sort");
            if (direction == "DESC") {
                _this.attr("data-direction", "ASC");
                var result = $(".home-backlinks tbody tr").sort(function(a, b) {
                    if (sort == "total") {
                        var contentA = parseInt($(a).find("td[data-key='" + sort + "']").text());
                        var contentB = parseInt($(b).find("td[data-key='" + sort + "']").text());
                    } else if (sort == "created") {
                        var contentA = parseInt($(a).find("td[data-key='" + sort + "']").attr("data-value"));
                        var contentB = parseInt($(b).find("td[data-key='" + sort + "']").attr("data-value"));
                    } else {
                        var contentA = $(a).find("td[data-key='" + sort + "'] .sort-text").text();
                        var contentB = $(b).find("td[data-key='" + sort + "'] .sort-text").text();
                    }
                    return (contentA < contentB) ? -1 : (contentA > contentB) ? 1 : 0;
                });
                $(".home-backlinks table tbody").html(result);
            } else {
                console.log(_this);
                _this.attr("data-direction", "DESC");
                var result = $(".home-backlinks tbody tr").sort(function(a, b) {
                    if (sort == "total") {
                        var contentA = parseInt($(a).find("td[data-key='" + sort + "']").text());
                        var contentB = parseInt($(b).find("td[data-key='" + sort + "']").text());
                    } else if (sort == "created") {
                        var contentA = parseInt($(a).find("td[data-key='" + sort + "']").attr("data-value"));
                        var contentB = parseInt($(b).find("td[data-key='" + sort + "']").attr("data-value"));
                        console.log(contentA);
                    } else {
                        var contentA = $(a).find("td[data-key='" + sort + "'] .sort-text").text();
                        var contentB = $(b).find("td[data-key='" + sort + "'] .sort-text").text();
                    }
                    return (contentA > contentB) ? -1 : (contentA < contentB) ? 1 : 0;
                });
                $(".home-backlinks table tbody").html(result);
            }
            let stt = 1;
            $(".home-backlinks tbody tr").each(function(e) {
                let _this = $(this);
                _this.find("td.col-stt").text(stt);
                stt++;
            });
        });

        $(".home-page .home-keywords .sort").click(function(e) {
            let _this = $(this);
            // $(".home-page .home-keywords .sort").removeClass("current");
            // _this.addClass("current");
            let direction = _this.attr("data-direction");
            let sort = _this.attr("data-sort");
            if (direction == "DESC") {
                _this.attr("data-direction", "ASC");
                var result = $(".home-keywords tbody tr").sort(function(a, b) {
                    if (sort == "total") {
                        var contentA = parseInt($(a).find("td[data-key='" + sort + "']").text());
                        var contentB = parseInt($(b).find("td[data-key='" + sort + "']").text());
                    } else if (sort == "created") {
                        var contentA = parseInt($(a).find("td[data-key='" + sort + "']").attr("data-value"));
                        var contentB = parseInt($(b).find("td[data-key='" + sort + "']").attr("data-value"));
                    } else {
                        var contentA = $(a).find("td[data-key='" + sort + "'] .sort-text").text();
                        var contentB = $(b).find("td[data-key='" + sort + "'] .sort-text").text();
                    }
                    return (contentA < contentB) ? -1 : (contentA > contentB) ? 1 : 0;
                });
                $(".home-keywords table tbody").html(result);
            } else {
                console.log(_this);
                _this.attr("data-direction", "DESC");
                var result = $(".home-keywords tbody tr").sort(function(a, b) {
                    if (sort == "total") {
                        var contentA = parseInt($(a).find("td[data-key='" + sort + "']").text());
                        var contentB = parseInt($(b).find("td[data-key='" + sort + "']").text());
                    } else if (sort == "created") {
                        var contentA = parseInt($(a).find("td[data-key='" + sort + "']").attr("data-value"));
                        var contentB = parseInt($(b).find("td[data-key='" + sort + "']").attr("data-value"));
                        console.log(contentA);
                    } else {
                        var contentA = $(a).find("td[data-key='" + sort + "'] .sort-text").text();
                        var contentB = $(b).find("td[data-key='" + sort + "'] .sort-text").text();
                    }
                    return (contentA > contentB) ? -1 : (contentA < contentB) ? 1 : 0;
                });
                $(".home-keywords table tbody").html(result);
            }
            let stt = 1;
            $(".home-keywords tbody tr").each(function(e) {
                let _this = $(this);
                _this.find("td.col-stt").text(stt);
                stt++;
            });
        });
        // cassiopeiaCreateBacklinkChart();
        // cassiopeiaCreateKeywordChart();

    });
})(jQuery);