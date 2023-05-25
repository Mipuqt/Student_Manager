<template>
    <div style="width: 100%;height: 100vh;background-color: #7ad0ff;overflow: hidden">
       <div style="width: 400px;margin:  150px auto">
           <div style="color: #ffffff;font-weight: bolder ;font-size: 35px;text-align: center;padding: 30px">欢迎注册</div>
           <el-form  :model="form" ref="form" :rules="rules">
               <el-form-item    prop="username">
                   <el-input     clearable prefix-icon="el-icon-user" v-model="form.username"></el-input>
               </el-form-item>
               <el-form-item  prop="password">
                   <el-input  clearable  prefix-icon="el-icon-lock"  v-model="form.password" show-password autocomplete="off"></el-input>
               </el-form-item>
               <el-form-item  prop="confirm">
                   <el-input  clearable   prefix-icon="el-icon-lock"  v-model="form.confirm" show-password autocomplete="off"></el-input>
               </el-form-item>

               <el-form-item >
                   <el-button style="width: 100%" type="primary" @click="register">注册</el-button>
               </el-form-item>
           </el-form>
       </div>
    </div>
</template>

<script>
    import request from "../utils/request";

    export default {
        name: "Login",
        data(){
            return{
                form:{},
                rules: {
                    username: [
                        { required: true, message: '请输入用户名', trigger: 'blur' },
                    ],
                    password: [
                        { required: true, message: '请输入密码', trigger: 'blur' },
                    ],
                    confirm: [
                        { required: true, message: '请确认密码', trigger: 'blur' },
                    ],
                },

            }
        },
        methods:{


            register(){
                this.$refs['form'].validate((valid) => {
                    if (valid) {
                        if( this.form.password!=this.form.confirm){
                            this.$message({
                                type: "error",
                                message: "两次密码不一至"
                            })
                        }else {
                            request.post("/user/register", this.form).then(res => {
                                if (res.code === '0') {
                                    this.$message({
                                        type: "success",
                                        message: '注册成功'
                                    })
                                    this.$router.push("/login")
                                } else {
                                    this.$message({
                                        type: "error",
                                        message: res.msg
                                    })

                                }

                            })
                        }

                    }
                })

            }
        }
    }
</script>

<style scoped>

</style>