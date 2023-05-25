<template>
    <div>
        <el-row >

        <allmap></allmap>

        </el-row>
<!--       <allmap></allmap>-->
    </div>
</template>

<script>

    import Allmap from "../views/student";
    export default {
        name: "main",
        components :{
            Allmap

        }
    }

</script>

<style scoped>
    .grid-content {
        border-radius: 4px;
        min-height: 36px;
    }
    .bg-purple-dark{
        background-color: #1875a1;
    }
</style>