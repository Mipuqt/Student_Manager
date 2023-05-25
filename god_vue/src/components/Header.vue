<template>
    <div style="line-height: 50px;height: 60px;border-bottom: 1px solid #ccc;display: flex;padding-right: -90px;">
        <div style="width: 190px;padding-left: 30px;color: #1875a1;font-weight:bolder;font-family: 'PingFang SC';">学生管理系统</div>
        <div style="flex: 1"></div>
        <div style="width: 90px;padding-top: 5px">
            <el-dropdown >
  <span class="el-dropdown-link" >
          <div class="block">
                    <el-avatar :size="45" :src="circleUrl">admin</el-avatar>
                </div>
  </span>
                <template #dropdown>
                    <el-dropdown-menu>

                        <el-dropdown-item index="/#">个人信息</el-dropdown-item>
                        <el-dropdown-item @click="$router.push('/login')">退出登录</el-dropdown-item>
                    </el-dropdown-menu>
                </template>
            </el-dropdown>
        </div>

    </div>
</template>

<script>
    export default {
        name: "Header",
        data(){
            return{
                user:{}
            }
        }
    }
</script>

<style >


</style>