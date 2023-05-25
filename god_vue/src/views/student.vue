<template>
  <div style="width: 100%">

    <el-button icon="el-icon-search" style="margin: 10px 60px" round @click="state.dialog = true">学生信息搜索</el-button>
    <el-card class="box-card" style="margin: 0px 60px" shadow="none">
      <template #header>
        <div class="card-header">
          <el-row :gutter="20">
            <el-col :span="3"> <span class="el-icon-user" style="font-size: 20px;margin-right: 20px"  >学生信息</span></el-col>
            <el-col :span="3"><el-select v-model="value" placeholder="班级筛选"  @change="getclass">
              <el-option
                  v-for="item in options"
                  :key="item.value"
                  :label="item.label"
                  :value="item.value">
              </el-option>
            </el-select></el-col>
            <el-col :span="3"> <el-button type="primary"  fixed="right" @click="state.dialogFormVisible = true,this.form={}" round>添加学生</el-button></el-col>
            <el-col :span="11" :offset="3">              <el-button type="primary"  fixed="right"  @click="download" round>导出当前表格</el-button>
            </el-col>

          </el-row>



        </div>
<!--        增加学生-->
        <el-dialog title="学生信息添加" v-model="state.dialogFormVisible">
          <el-form :model="form" :rules="rules" ref="ruleForm" label-width="100px" class="demo-ruleForm">
            <el-form-item label="姓名" prop="name">
              <el-input v-model="form.name"></el-input>
            </el-form-item>
            <el-form-item label="班级" prop="classroom">
              <el-select v-model="form.classroom" placeholder="请选择班级">
                <el-option label="一班" value="一班"></el-option>
                <el-option label="二班" value="二班"></el-option>
              </el-select>
            </el-form-item>
            <el-form-item label="出生日期" prop="date">
              <el-col :span="11">
                <el-date-picker type="date" placeholder="选择日期"   v-model="form.date" value-format="YYYY-MM-DD"  style="width: 100%;"></el-date-picker>
              </el-col>
            </el-form-item>
            <el-form-item label="性别" prop="sex">
              <el-radio-group v-model="form.sex">
                <el-radio label="男"></el-radio>
                <el-radio label="女"></el-radio>
              </el-radio-group>
            </el-form-item>
            <el-form-item label="手机号" prop="num">
              <el-input v-model="form.num"></el-input>
            </el-form-item>
            <el-form-item>
              <el-button type="primary" @click="onSubmit('ruleForm')">提交</el-button>
              <el-button  @click="state.dialogFormVisible = false">取消</el-button>
            </el-form-item>
          </el-form>
        </el-dialog>

      </template>
      <el-table
          :data="tableData"
          border
          style="width: 55%">
        <el-table-column
            fixed
            prop="id"
            label="学号"
            width="120">
        </el-table-column>
        <el-table-column
            prop="name"
            label="姓名"
            width="120">
        </el-table-column>
        <el-table-column
            prop="sex"
            label="性别"
            width="120">
        </el-table-column>
        <el-table-column
            prop="date"
            label="出生日期"
            width="120">
        </el-table-column>
        <el-table-column
            prop="num"
            label="联系电话"
            width="120">
        </el-table-column>
        <el-table-column
            prop="classroom"
            label="班级"
            width="150">
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
      </el-table>
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
              :loading="state.mainloading"
              @click="getstu"
          >{{ state.mainloading ? '检索中 ...' : '搜索' }}
          </el-button
          >
        </div>
      </div>
    </el-drawer>
  </div>

</template>

<script>
import request from "../utils/request";
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

    value: '',
      state: {
        maploading:false,
        dialog: false,
        dialogFormVisible: false,
        action:1,
      },
      rules: {
        name: [
          { required: true, message: '请输入学生姓名', trigger: 'blur' },
          { min: 3, max: 10, message: '长度在 2 到 10 个字符', trigger: 'blur' }
        ],
        classroom: [
          { required: true, message: '请选择班级', trigger: 'change' }
        ],
        date: [
          { type: 'date', required: true, message: '请选择日期', trigger: 'change' }
        ],
        sex: [
          { required: true, message: '请选择性别', trigger: 'change' }
        ],
        num: [
          { required: true, message: '请填写手机号', trigger: 'blur' },
          { min: 11, max: 11, message: '请填写11位手机号', trigger: 'blur' }
        ]
      },
      tableData: [],
      Idform:'',
      form: {
        name: '',
        classroom: '',
        date: '',
        sex: '',
        num:'',
      },
      formLabelWidth: '120px'

    }
  },
  mounted() {
    this.getAllInfo()
  },
  methods: {
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
    },
    // 班级筛选
    getclass(){
      console.log(this.value)
      request.post('/main/getClass?classroom='+this.value).then(res => {
        this.tableData=res.data
      })

    },
    //学号查询
    getstu(){
      console.log(this.Idform)
      request.post('/main/getstu?id='+this.Idform).then(res => {
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
      this.form=row
      this.state.action=0
      this.state.dialogFormVisible=true

    },
    //删除学生
    handdelte(row) {
      console.log(row.id)
      this.$confirm('此操作将永久删除该文件, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        request.post('/main/delete?id='+row.id).then(res => {
          this.$message({
            type: 'success',
            message: '删除成功!'
          });
          this.getAllInfo()
      }).catch(err=>{
          this.$message({
            type: 'success',
            message: '删除失败，请清除此学生成绩!'
          });
        })

      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消删除'
        });
      });
    },
    getmap() {
      this.state.maploading=true
      request.get('/data/map?name=' + this.NowBreath[0].shipName).then(res => {
        this.dataList = res.data
        this.state.innerPro = true
        this.mapflag = true
        this.state.maploading=false
      })

    },
    //添加学生
    onSubmit(formName){
      console.log(this.form)
      if (this.state.action==1){
        this.$refs[formName].validate((valid) => {
          if (valid) {
            request.post('/main/add',this.form).then(res => {
              this.getAllInfo()
              this.state.dialogFormVisible=false;
              this.$message({
                message: '添加成功',
                type: 'success'
              });
            })
          } else {
            console.log('error submit!!');
            return false;
          }
        });
      }else {
        this.$refs[formName].validate((valid) => {
          if (valid) {
            request.post('/main/edit',this.form).then(res => {
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
      request.get('/main/studentInfo').then(res=>{
        this.tableData=res.data;
      })
    },
    //数据导出
    exportData() {
      let data = JSON.stringify(this.tableData);
      let blob = new Blob([data], { type: "application/json" });
      FileSaver.saveAs(blob, `学生数据.json`);
    },


  }
}
</script>

<style scoped>
.demo-drawer__footer {
  margin-left: 80px;
}

.demo-table-expand {
  font-size: 0;
}

.demo-table-expand label {
  width: 90px;
  color: #99a9bf;
}

.demo-table-expand .el-form-item {
  margin-right: 0;
  margin-bottom: 0;
  width: 50%;
}

list_info > p {
  line-height: 20px;
  background-color: #1875a1;
}
</style>