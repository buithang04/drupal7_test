var footer = jQuery("footer");

function cassiopeiaCreateBacklinkChart() {
    let maxNumber = jQuery("#max-num").val();
    let xValues = jQuery("#ValueX").val();
    let dataBackLink = jQuery("#dataBackLink").val();
    let dataDomain = jQuery("#dataDomain").val();
    // console.log("dataBackLink",dataBackLink);
    new Chart("back_link_chart", {
        type: "line",
        data: {
            labels: JSON.parse(xValues),
            datasets: [{
                    label: "Số lượng backlink",
                    data: JSON.parse(dataBackLink),
                    borderColor: "#0084ff",
                    backgroundColor: "#0084ff",
                    fill: false,
                },
                {
                    label: "Số lượng domain",
                    data: JSON.parse(dataDomain),
                    borderColor: "#e8d420",
                    backgroundColor: "#e8d420",
                    fill: false,
                },
            ]
        },
        options: {
            plugins: {
                legend: {
                    position: 'bottom',
                    align: 'center',
                }
            },
            scales: {
                y: {
                    min: 0,
                    max: parseInt(maxNumber)
                }
            },
            elements: {
                arc: {
                    weight: 0,
                }
            }
        }
    });
}

function cassiopeiaBackLinkRelChart() {
    var xValues = ["Dofollow", "Nofollow", "Sponsored", "UGC"];
    let dataRel = jQuery("#dataRel").val();
    // var yValues = [55, 49, 44, 24, 15];
    var barColors = [
        "#348FE3",
        "#06C5D1",
        "#FBCA4D",
        "#9DD246",
        // "#1e7145"
    ];

    new Chart("back_link_rel_chart", {
        type: 'doughnut',
        data: {
            labels: xValues,
            datasets: [{
                backgroundColor: barColors,
                data: JSON.parse(dataRel),
            }]
        },
        options: {
            responsive: true,
            // legend: {
            //     position: 'right',
            //     onClick: function() {
            //         return null;
            //     },
            //     labels: {
            //         boxWidth: 30,
            //         generateLabels: function(chart) {
            //             return chart.data.labels.map(function(label, i) {
            //                 return {
            //                     text: label,
            //                     fillStyle: chart.data.datasets[0].backgroundColor[i]
            //                 };
            //             });
            //         }
            //     }
            // },
            plugins: {
                legend: {
                    position: 'right',
                    align: 'center',
                    display: false,
                }
            },
            elements: {
                arc: {
                    weight: 0,
                }
            }
            // title: {
            //     display: true,
            //     text: 'My Bar Chart'
            // },
        }
    });
}

function cassiopeiaIndexChart() {
    var xValues = ["GG Indexed", "Not Indexed"];
    let dataIndex = jQuery("#indexChartData").val();
    var barColors = [
        "#716EEE",
        "#24CECE",
    ];

    new Chart("back_link_index_chart", {
        type: 'doughnut',
        data: {
            labels: xValues,
            datasets: [{
                backgroundColor: barColors,
                data: JSON.parse(dataIndex),
            }]
        },
        options: {
            responsive: true,
            plugins: {
                legend: {
                    position: 'right',
                    align: 'center',
                    display: false,
                }
            }
            // title: {
            //     display: true,
            //     text: 'My Bar Chart'
            // },
        }
    });
}
(function($) {
    $("document").ready(function(e) {
        let date_filter = $("select[name='date_filter']");
        date_filter.change(function(e) {
            if (date_filter.val() === "other") {
                $(".container-inline-date").addClass("active");
            } else {
                $(".container-inline-date").removeClass("active");
            }
        });
        console.log(date_filter.val());
        if (date_filter.val() === "other") {
            $(".container-inline-date").addClass("active");
        } else {
            $(".container-inline-date").removeClass("active");
        }
        cassiopeiaCreateBacklinkChart();
        cassiopeiaBackLinkRelChart();
        cassiopeiaIndexChart();
    });
})(jQuery);