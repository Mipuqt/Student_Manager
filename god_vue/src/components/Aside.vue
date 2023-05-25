<template>
    <div>

        <el-menu style="height: calc(100vh - 90px);margin: 0 0;padding: 0 0"
                 :default-active="path"
                 router
                 :collapse="isCollapse"
                 class="el-menu-vertical-demo"
                 >
            <br>
            <el-menu-item index="/#">
                <i class="el-icon-menu"></i>
                <template #title>学生基本信息</template>
            </el-menu-item>
            <el-menu-item index="/cen" >
                <i class="el-icon-document"></i>
                <template #title>考试成绩管理👂</template>
            </el-menu-item>
            <el-divider><i class="el-icon-star-on"></i></el-divider>
            <el-tooltip
                    class="item"
                    effect="light"
                    :content="ifexport"
                    placement="bottom"
            >
                    <el-menu-item @click="Switch" >
                        <i class="el-icon-s-unfold" style="font-size: 25px;" v-if="isCollapse"></i>
                        <i class="el-icon-s-fold" style="font-size: 25px;"  v-else></i>
                    </el-menu-item>
            </el-tooltip>


        </el-menu>

    </div>
</template>

<script>
    export default {
        name: "Aside1",
        data() {
            return {
                path: this.$route.path,
                isCollapse: false,
                arrow: true,
                ifexport: "折叠",
            }
        },
        methods: {
            Switch() {
                this.isCollapse = !this.isCollapse
                if (this.isCollapse) {
                    this.ifexport = "展开"
                } else {
                    this.ifexport = "折叠"
                }
            }
        }
    }
</script>

<style scoped>
    .el-menu-vertical-demo:not(.el-menu--collapse) {
        width: 160px;
    }

</style>