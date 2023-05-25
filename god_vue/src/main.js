import {createApp} from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'
import installElementPlus from './plugins/element'
// import {vue3JsonExcel} from "vue3-json-excel"

const app = createApp(App)
// app.config.devtools=true
installElementPlus(app)
// app.component("downloadExcel", JsonExcel);
app.use(store).use(router).mount('#app')
