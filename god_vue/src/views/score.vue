<template>
  <div style="width: 100%">

    <el-button icon="el-icon-search" style="margin: 10px 60px" round @click="state.dialog = true">考试成绩查询</el-button>
    <el-card class="box-card" style="margin: 0px 60px" shadow="none">
      <template #header>
        <div class="card-header">
          <el-row :gutter="20">
            <el-col :span="3"> <span class="el-icon-s-order" style="font-size: 20px;margin-right: 20px"  >考试信息</span></el-col>
            <el-col :span="3"><el-select v-model="value.classroom" placeholder="班级筛选"  @change="getclass">
              <el-option
                  v-for="item in options"
                  :key="item.value"
                  :label="item.label"
                  :value="item.value">
              </el-option>
            </el-select>
            </el-col>
              <el-col :span="3"><el-select v-model="value.stype" placeholder="考试筛选"  @change="getclass">
                <el-option
                    v-for="item in options1"
                    :key="item.value"
                    :label="item.label"
                    :value="item.value">
                </el-option>
              </el-select>
              </el-col>

            <el-col :span="6"> <el-button type="primary"  fixed="right" @click="state.dialogFormVisible = true,this.form={}" round>成绩录入</el-button>

<!--              <el-button type="primary"  fixed="right"  @click="exportData" round>导出当前表格</el-button>-->
              <el-button type="primary"  fixed="right"  @click="download" round>导出当前表格</el-button>
            </el-col>


          </el-row>



        </div>
        <!--        增加学生-->
        <el-dialog title="考生成绩添加" v-model="state.dialogFormVisible">
          <el-form :model="form" :rules="rules" ref="ruleForm" label-width="100px" class="demo-ruleForm">
            <el-form-item label="学号" prop="stuid">
              <el-input v-model="form.stuid"></el-input>
            </el-form-item>
            <el-form-item label="科目" prop="type">
              <el-select v-model="form.type" placeholder="请选择科目">
                <el-option label="语文" value="1"></el-option>
                <el-option label="数学" value="2"></el-option>
                <el-option label="英语" value="3"></el-option>
              </el-select>
            </el-form-item>
            <el-form-item label="成绩" prop="score">
              <el-input v-model="form.score"></el-input>
            </el-form-item>
            <el-form-item label="考试类型" prop="stype">
              <el-input v-model="form.stype"></el-input>
            </el-form-item>
            <el-form-item>
              <el-button type="primary" @click="onSubmit('ruleForm')">提交</el-button>
              <el-button  @click="state.dialogFormVisible = false">取消</el-button>
            </el-form-item>
          </el-form>
        </el-dialog>

      </template>
      <el-row :gutter="25">
        <el-col :span="16"><el-table
            :data="tableData"
            border
            style="width: 80%">
          <el-table-column
              fixed
              prop="stuid"
              label="学号"
              width="120">
          </el-table-column>
          <el-table-column
              prop="name"
              label="姓名"
              width="120">
          </el-table-column>
          <el-table-column
              prop="stype"
              label="考试"
              width="120">
          </el-table-column>
          <el-table-column
              prop="cname"
              label="科目"
              width="120">
          </el-table-column>
          <el-table-column
              prop="score"
              label="成绩"
              width="120">
          </el-table-column>
          <el-table-column
              prop="classroom"
              label="班级"
              width="120">
          </el-table-column>
          <el-table-column
              fixed="right"
              label="操作"
              width="100">
            <template #default="scope">
              <el-button @click="handdelte(scope.row)" type="text" size="small">删除</el-button>
              <el-button type="text" size="small" @click="edit(scope.row)">编辑</el-button>
            </template>
          </el-table-column>
        </el-table></el-col>
        <el-col :span="7"><el-table
            :data="exinfo"
            border
            style="width: 80%">
          <el-table-column
              fixed
              prop="stype"
              label="考试类型"
              width="120">
          </el-table-column>
          <el-table-column
              prop="count"
              label="考试人数"
              width="120">
          </el-table-column>
          <el-table-column
              fixed="right"
              label="操作"
              width="100">
            <template #default="scope">
              <el-button @click="deletex(scope.row)" type="text" size="small">删除该考试</el-button>
            </template>
          </el-table-column>
        </el-table></el-col>
      </el-row>

    </el-card>

    <!--学号搜索-->
    <el-drawer
        ref="drawer"
        v-model="state.dialog"
        title="学生信息搜索"
        direction="rtl"
        custom-class="demo-drawer"
    >
      <div class="demo-drawer__content" style="width: 80%;padding-right: 20%">
        <el-form :model="Idform">
          <el-form-item label="学号">
            <el-input v-model="Idform" size="small" autocomplete="true" clearable/>
          </el-form-item>
        </el-form>
        <div class="demo-drawer__footer">
          <el-button @click="cancelForm">Cancel</el-button>
          <el-button
              type="primary"
              :loading="state.scoreloading"
              @click="getstu"
          >{{ state.scoreloading ? '检索中 ...' : '搜索' }}
          </el-button
          >
        </div>
      </div>
    </el-drawer>
  </div>

</template>

<script>
import request from "../utils/request";
// import JsonCsv from "vue-json-csv";
import json2csv from 'json2csv'
import FileSaver from "file-saver";
export default {
  name: "student",
  data() {
    return {
      options: [{
        value: '一班',
        label: '一班'
      }, {
        value: '二班',

        label: '二班'
      }],
      options1: [{
        value: '模拟考',
        label: '模拟考'
      }, {
        value: '省考',
        label: '省考'
      }],
      value: {},
      state: {
        maploading:false,
        dialog: false,
        dialogFormVisible: false,
        action:1,
      },
      rules: {
        stuid: [
          { required: true, message: '请输入学号', trigger: 'blur' },
        ],
        type: [
          { required: true, message: '请选择考试科目', trigger: 'change' }
        ],
        stype: [
          { required: true, message: '请输入考试类型', trigger: 'blur' }
        ],
        score: [
          { required: true, message: '请填写考生成绩', trigger: 'blur' },
        ]
      },
      tableData: [],
      exinfo: [],
      Idform:'',
      form: {
        score: '',
        type: '',
        stype: '',
        stuid:''
      },

    }
  },
  mounted() {
    this.getAllInfo()
  },
  methods: {
    // 班级筛选
    getclass(){
      console.log(this.value)
      request.post('/score/search',this.value).then(res => {
        this.tableData=res.data
      })

    },
    //学号查询
    getstu(){
      console.log(this.Idform)
      request.post('/score/getstu?id='+this.Idform).then(res => {
        console.log((res.data).length)
        if(res.data==false){
          this.$message({
            type: 'info',
            message: '无此学生'
          });
        }else {
          this.tableData=res.data
          this.state.dialog=false
        }

      })

    },
    cancelForm(){
      this.state.dialog=false;
    },
    //修改信息
    edit(row){
      console.log(row)
      this.form=row
      this.state.action=0
      this.state.dialogFormVisible=true

    },
    //删除学生
    handdelte(row) {
      console.log(row.sid)
      this.$confirm('此操作将永久删除该考试, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        request.post('/score/delete?sid='+row.sid).then(res => {
          this.$message({
            type: 'success',
            message: '删除成功!'
          });
          this.getAllInfo()
        })

      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消删除'
        });
      });
    },
    //删除考试
    deletex(row) {
      console.log(row.stype)
      this.$confirm('此操作将永久删除该考试, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        request.post('/score/deleteex?stype='+row.stype).then(res => {
          this.$message({
            type: 'success',
            message: '删除成功!'
          });
          this.getAllInfo()
        })

      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消删除'
        });
      });
    },

    //添加成绩
    onSubmit(formName){
      if (this.state.action==1){
        this.$refs[formName].validate((valid) => {
          console.log(this.form)
          if (valid) {
            request.post('/score/add',this.form).then(res => {
              this.getAllInfo()
              this.state.dialogFormVisible=false;
              this.$message({
                message: '添加成功',
                type: 'success'
              });
            }).catch(err=> {
              this.$message({
                message: '学号不存在',
                type: 'success'
              });
            })
          } else {
            console.log('error submit!!');
            this.$message({
              message: '学号不存在',
              type: 'error'
            });
            return false;
          }
        });
      }else {
        this.$refs[formName].validate((valid) => {
          if (valid) {
            request.post('/score/edit',this.form).then(res => {
              this.state.dialogFormVisible=false;
              this.getAllInfo()
              this.$message({
                message: '修改成功',
                type: 'success'
              });
            })
          } else {
            console.log('error submit!!');
            return false;
          }
        });
      }

    },
    //获取总数据
    getAllInfo(){
      request.get('/score/getall').then(res=>{
        this.tableData=res.data;
      })
      request.get('/score/getex').then(res=>{
        this.options1=res.data;
      })
      request.get('/score/getexinfo').then(res=>{
        this.exinfo=res.data;
      })
    },
    //数据导出
    exportData() {
      let data = JSON.stringify(this.tableData);
      let blob = new Blob([data], { type: "application/json" });
      FileSaver.saveAs(blob, `学生数据.json`);
    },
    download(){
      //datas：数据，fields：字段名
      try {
        const result = json2csv.parse(this.tableData, {
          fields: this.fields
        });
        // 判断浏览器类型
        if ((navigator.userAgent.indexOf('compatible') > -1 &&
                navigator.userAgent.indexOf('MSIE') > -1) ||
            navigator.userAgent.indexOf('Edge') > -1) {
          //IE10或Edge浏览器
          var BOM = "\uFEFF";
          var csvData = new Blob([BOM + result], { type: "text/csv" });
          navigator.msSaveBlob(csvData, `test.csv`);
        } else {
          //非IE浏览器
          var csvContent = "data:text/csv;charset=utf-8,\uFEFF" + result;
          //使用a标签的download属性实现下载功能
          var link = document.createElement("a");
          link.href = encodeURI(csvContent);
          link.download = `test.csv`;
          document.body.appendChild(link);
          link.click();
          document.body.removeChild(link);
        }
      } catch (err) {
        alert(err);
      }
    }


  }
}
</script>

<style scoped>
.demo-drawer__footer {
  margin-left: 80px;
}


list_info > p {
  line-height: 20px;
  background-color: #1875a1;
}
</style>