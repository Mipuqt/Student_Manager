<template>
    <el-col>
        <div id="china_chart" class="grid-content bg-purple-dark" style="height: calc(100vh - 62px);"></div>
    </el-col>
    <!--    <div id="china_chart" style="width: calc(100vh - 10px);height:45vw;"></div>-->

</template>

<script>
    import echarts from "../assets/js/echarts.min"
    import china from "../assets/json/中华人民共和国.json";
    import jiangsu from "../assets/json/江苏省.json"
    import shanghai from "../assets/json/上海市.json"
    import request from "../utils/request";

    export default {
        name: "allmap",
        data() {
            return {

                  typeflag:false,
                  godsflag:false,
                  proflag:false,
                typedata:[],
                prodata:[],
                gods:[],
                data: [
                    {
                        name: 'Apples',
                        value: 70
                    },
                    {
                        name: 'Strawberries',
                        value: 68
                    },
                    {
                        name: 'Bananas',
                        value: 48
                    },
                    {
                        name: 'Oranges',
                        value: 40
                    },
                    {
                        name: 'Pears',
                        value: 32
                    },
                    {
                        name: 'Pineapples',
                        value: 27
                    },
                    {
                        name: 'Grapes',
                        value: 18
                    }
                ],
            }

        },
        mounted() {
            this.showChart();
        },
        methods: {
            showChart() {
                // get_data()
                //定义一个全局变量，用来统计每个省有几个市
                let num = 0;
                //获取到需要添加地图的位置
                var myChart = echarts.init(document.getElementById('china_chart'));
                let mapname = china;
                //设置省份的json 这里注意名字要和中国地图上的名字一致
                var mapJson = [
                    {
                        name: "江苏",
                        json: jiangsu
                    },
                    {
                        name: "上海",
                        json: shanghai
                    }];

                //提取自动播放的代码
                function timing() {
                    if (mapname == china) {
                        // 取消高亮指定的数据图形
                        myChart.dispatchAction({
                            type: 'downplay',
                            seriesIndex: 0,
                            dataIndex: index,
                        });
                        // 高亮指定的数据图形
                        myChart.dispatchAction({
                            type: 'highlight',
                            seriesIndex: 0,
                            dataIndex: index + 1,
                        });
                        index++;
                        if (index > num) {
                            index = -1;
                        }
                    }
                }

                //加载时的文字提示
                myChart.showLoading({text: '正在加载数据'});  //增加等待提示
                //设置开始位置（播放的位置）
                let index = -1;
                //定时播放
                var timer = setInterval(function () {
                    //调用定时播放代码
                    timing()
                }, 1500);
                //鼠标移入
                myChart.on('mousemove', function (e) {
                    //取消定时
                    if (e.componentSubType == "map") {
                        clearInterval(timer);
                        //取消高亮
                        myChart.dispatchAction({
                            type: 'downplay',
                            seriesIndex: 0,
                        });
                        //高亮鼠标移入的位置
                        myChart.dispatchAction({
                            type: 'highlight',
                            seriesIndex: 0,
                            dataIndex: e.dataIndex,
                        });
                    }

                });
                //鼠标移出
                myChart.on('mouseout', function (e) {
                    //取消定时
                    clearInterval(timer);
                    //取消高亮
                    myChart.dispatchAction({
                        type: 'downplay',
                        seriesIndex: 0,
                        dataIndex: e.dataIndex,
                    });
                    //重新开始定时播放
                    timer = setInterval(function () {
                        //调用定时播放代码
                        timing()
                    }, 2000);
                });
                //点击事件
                myChart.on('click', function (e) {
                    //我们根据名字来判断是否选择一种
                    if (e.name != china) {
                        for (var i = 0; i < mapJson.length; i++) {
                            if (mapJson[i].name == e.name) {
                                mapname = mapJson[i].json
                                mapInit(mapname, e.name);
                            } else {
                            }
                        }
                        myChart.getZr().on('click', params => {
                            if (params.target) {
                            } else {
                                mapname = china;
                                mapInit(mapname);

                            }

                        })
                    }

                });
                //设置初始化时间

                setTimeout( ()=> {
                    request.get("/main/shiptype").then(res=>{
                        this.typedata=res.data
                        console.log(this.typedata)
                        this.typeflag=true
                        if (this.typeflag&&this.proflag&&this.godsflag){
                            mapInit(mapname);
                        }
                    })

                    request.get("/main/prodata").then(res=>{
                        this.prodata=res.data
                        console.log(this.prodata)
                        this.proflag=true
                        if (this.typeflag&&this.proflag&&this.godsflag){
                            // this.showChart();
                            mapInit(mapname);
                        }
                    })
                    request.get("/main/gods").then(res=>{
                        this.gods=res.data
                        console.log(this.gods)
                        this.godsflag=true
                        if (this.typeflag&&this.proflag&&this.godsflag){
                            // this.showChart();
                            mapInit(mapname);
                        }
                    })
                    // mapInit(mapname);
                }, 10);


                //创建地图
                var mapInit = (mapname, proname = '全国') => {
                    //调用中国地图（同步）
                    //获取到长度（每个省里有几个市）
                    num = mapname.features.length;
                    //调用我们通过json对象注册的地图
                    echarts.registerMap('China', mapname);
                    //文件加载的动画
                    myChart.hideLoading();
                    //判断是否为祖国地图
                    if (mapname === china) {
                        //设置小黄点
                        var geoCoordMap = {
                            '台湾': [122, 23],
                            '黑龙江': [129, 51],
                            '内蒙古': [110.3467, 41.4899],
                            "吉林": [125.8154, 44.2584],
                            '北京市': [116.4551, 40.2539],
                            "辽宁": [123.1238, 42.1216],
                            "河北": [114.4995, 38.1006],
                            "天津": [117.4219, 39.4189],
                            "山西": [112.3352, 37.9413],
                            "陕西": [109.1162, 34.2004],
                            "甘肃": [103.5901, 36.3043],
                            "宁夏": [106.3586, 38.1775],
                            "青海": [101.4038, 36.8207],
                            "新疆": [87.9236, 43.5883],
                            "西藏": [88.388277, 31.56375],
                            "四川": [103.9526, 30.7617],
                            "重庆": [108.384366, 30.439702],
                            "山东": [117.1582, 36.8701],
                            "河南": [113.4668, 34.6234],
                            "江苏": [118.8062, 31.9208],
                            "安徽": [117.29, 32.0581],
                            "湖北": [114.3896, 30.6628],
                            "浙江": [119.5313, 29.8773],
                            "福建": [119.4543, 25.9222],
                            "江西": [116.0046, 28.6633],
                            "湖南": [113.0823, 28.2568],
                            "贵州": [106.6992, 26.7682],
                            "云南": [102.9199, 25.4663],
                            "广东": [113.12244, 23.009505],
                            "广西": [108.479, 23.1152],
                            "海南": [110.3893, 19.8516],
                            '上海': [121.4648, 31.2891],
                        };
                        //设置每个区域的值
                        var data= [
                            {name:"台湾",value:1},
                            {name:"北京",value:2},
                            {name:"天津",value:3},
                            {name:"河北",value:4},
                            {name:"山西",value:5},
                            {name:"内蒙古",value:6},
                            {name:"辽宁",value:7},
                            {name:"吉林",value:8},
                            {name:"黑龙江",value:9},
                            {name:"上海",value:10},
                            {name:"江苏",value:11},
                            {name:"浙江",value:12},
                            {name:"安徽",value:13},
                            {name:"福建",value:14},
                            {name:"江西",value:15},
                            {name:"山东",value:16},
                            {name:"河南",value:17},
                            {name:"湖北",value:18},
                            {name:"湖南",value:19},
                            {name:"重庆",value:20},
                            {name:"四川",value:21},
                            {name:"贵州",value:22},
                            {name:"云南",value:23},
                            {name:"西藏",value:24},
                            {name:"陕西",value:25},
                            {name:"甘肃",value:26},
                            {name:"青海",value:27},
                            {name:"宁夏",value:28},
                            {name:"新疆",value:29},
                            {name:"广东",value:30},
                            {name:"广西",value:31},
                            {name:"海南",value:32},
                        ]
                        //给每个地区赋值
                        var convertData = function (data) {
                            //定义一个数组
                            var res = [];
                            //循环遍历每个区域值
                            for (var i = 0; i < data.length; i++) {
                                //获取坐标
                                var geoCoord = geoCoordMap[data[i].name];
                                //判断是否有坐标
                                if (geoCoord) {
                                    //往数组里设置值
                                    res.push({
                                        name: data[i].name,
                                        value: geoCoord.concat(data[i].value)
                                    });
                                }
                            }
                            return res;
                        };
                    } else {
                        //这里不为中国地图所以先不设置（后面需要对市区进行标记在设置）

                        //设置小黄点
                        var geoCoordMap = {};
                        //设置每个区域的值
                        var data = [];
                        //给每个地区赋值
                        convertData = function (data) {
                            var res = [];
                            for (var i = 0; i < data.length; i++) {
                                var geoCoord = geoCoordMap[data[i].name];
                                if (geoCoord) {
                                    res.push({
                                        name: data[i].name,
                                        value: geoCoord.concat(data[i].value)
                                    });
                                }
                            }
                            return res;
                        };
                    }


                    //地图开始
                    let option = {
                        title: [{
                            text: proname + "货运信息统计",
                            left: "36%",
                            top:"5%"
                        }, {
                            subtext: '船舶类型',
                            left: '10%',
                            top: "30%",
                            textAlign: 'center'
                        },
                            {
                                subtext: '货物类型统计',
                                left: '10%',
                                top: '62%',
                                textAlign: 'center'
                            },
                            {
                                subtext: '省份活跃度',
                                left: '15%',
                                top: '92%',
                                textAlign: 'center'
                            }
                        ],
                        //设置背景颜色
                        // legend: {},
                        tooltip: {
                            trigger: 'item',
                            axisPointer:{
                                type:'shadow'
                            }

                        },
                        backgroundColor: '#020933',
                        grid: [{
                            left: '70%',
                            bottom: '60%',
                            top: "12%",
                            right:'5%'
                        }, {
                            left: '65%',
                            bottom: "10%",
                            top: '55%',
                            right:'5%'
                        }],
                        xAxis: [{
                            type: 'category',
                            gridIndex: 0,
                            data: ['Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun']

                        },
                            {
                            gridIndex: 1,
                            type:'category'
                        }],
                        yAxis: [{
                            type: 'value',
                            gridIndex: 0
                        },
                            {
                            type:'value',
                            gridIndex: 1
                        }],

                        geo: {
                            map: 'China',//地图为刚刚设置的China
                            left: "23%",
                            aspectScale: 0.73, //长宽比
                            zoom: 1.15,//当前视角的缩放比例
                            roam: false,//是否开启鼠标缩放和平移漫游。默认不开启。如果只想要开启缩放或者平移，可以设置成 'scale' 或者 'move'。设置成 true 为都开启
                            itemStyle: {//地图区域的多边形 图形样式
                                normal: {
                                    areaColor: '#013C62',//地区颜色
                                    shadowColor: '#182f68',//阴影颜色
                                    shadowOffsetX: 0,//阴影偏移量
                                    shadowOffsetY: 25,//阴影偏移量
                                },
                                emphasis: {
                                    areaColor: '#2AB8FF',//地区颜色
                                    label: {
                                        show: false,//是否在高亮状态下显示标签
                                    },
                                },
                            },
                        },

                        series: [//数据系列
                            {
                                type: 'map',//地图类型
                                left: "23%",
                                //地图上文字
                                label: {
                                    normal: {
                                        show: true,//是否显示标签
                                        textStyle: {
                                            color: '#fff',
                                        },
                                    },
                                    emphasis: {
                                        textStyle: {
                                            color: '#fff',
                                        },
                                    },
                                },
                                //地图区域的多边形 图形样式
                                itemStyle: {
                                    normal: {
                                        borderColor: '#2ab8ff',
                                        borderWidth: 1.5,
                                        areaColor: '#12235c',
                                    },
                                    emphasis: {
                                        areaColor: '#2AB8FF',
                                        borderWidth: 0,
                                    },
                                },
                                zoom: 1.2,//当前视角的缩放比例
                                //是否开启鼠标缩放和平移漫游。默认不开启。如果只想要开启缩放或者平移，可以设置成 'scale' 或者 'move'。设置成 true 为都开启
                                roam: false,
                                map: 'China', //使用中国地图

                            },
                            {

                                //设置为分散点
                                type: 'scatter',
                                //series坐标系类型
                                coordinateSystem: 'geo',
                                //设置图形 'circle', 'rect', 'roundRect', 'triangle', 'diamond', 'pin', 'arrow'
                                symbol: 'pin',
                                // //标记的大小，可以设置成诸如 10 这样单一的数字，也可以用数组分开表示宽和高，例如 [20, 10] 表示标记宽为20，高为10
                                symbolSize: [40, 40],
                                //气泡字体设置
                                label: {
                                    normal: {
                                        show: true,//是否显示
                                        textStyle: {
                                            color: '#fff',//字体颜色
                                            fontSize: 8,//字体大小
                                        },
                                        //返回气泡数据
                                        formatter(value) {
                                            return value.data.value[2]
                                        }
                                    }
                                },
                                itemStyle: {
                                    normal: {
                                        color: '#1E90FF', //标志颜色
                                    }
                                },
                                //给区域赋值
                                data: convertData(data),
                                showEffectOn: 'render',//配置何时显示特效。可选：'render' 绘制完成后显示特效。'emphasis' 高亮（hover）的时候显示特效。
                                rippleEffect: {//涟漪特效相关配置。
                                    brushType: 'stroke'//波纹的绘制方式，可选 'stroke' 和 'fill'
                                },
                                hoverAnimation: true,//是否开启鼠标 hover 的提示动画效果。
                                zlevel: 1//所属图形的 zlevel 值
                            },
                            {
                                type: 'pie',
                                radius: '20%',
                                center: ['10%', '20%'],
                                data: this.typedata,
                                label: {
                                    position: 'outer',
                                    // alignTo: 'none',
                                    bleedMargin: 5
                                },
                            },
                            {
                                type: 'pie',
                                radius: '20%',
                                center: ['10%', '50%'],
                                data: this.prodata,
                                label: {
                                    position: 'outer',
                                    // alignTo: 'labelLine',
                                    bleedMargin: 5
                                },

                            },
                            {
                                type: 'pie',
                                radius: '20%',
                                center: ['15%', '80%'],
                                data: this.gods,
                                label: {
                                    position: 'outer',
                                    margin: 20
                                },

                            },
                            {
                                name:"国内",
                                data: [10, 11, 13, 11, 12, 12, 9],
                                type: 'line',
                                xAxisIndex:0,
                                markPoint: {
                                    data: [
                                        { type: 'max', name: 'Max' },
                                        { type: 'min', name: 'Min' }
                                    ]
                                },
                                yAxisIndex:0
                            },
                            {
                                name:"国外",
                                data: [1, -2, 2, 5, 3, 2, 0],
                                type: 'line',
                                xAxisIndex:0,
                                yAxisIndex:0
                            },


                            {
                                data: [150, 230, 224, 218, 135, 147, 260],
                                type: 'line',
                                xAxisIndex: 1,
                                yAxisIndex: 1
                            }


                        ],
                    };
                    myChart.setOption(option);

                };
            }
        }
    }
</script>

<style scoped>

</style>