<template>
  <el-config-provider :locale="locale">
    <div>
      <router-view />
    </div>
  </el-config-provider>
</template>

<script>
  import {ElConfigProvider} from  'element-plus'
  import zhCn from 'element-plus/lib/locale/lang/zh-cn'



  export default {
    name: 'app',
    components :{
    },
    data(){
      return{
        locale:zhCn
      }
    },
    components: {
      [ElConfigProvider.name]: ElConfigProvider,

    }
  }
</script>

<style>
  *{
    margin: 0px 0px;
    padding: 0px 0px;
    padding-right: 0px;
  }

</style>
