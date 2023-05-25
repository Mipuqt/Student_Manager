import {createRouter, createWebHistory} from 'vue-router'
import Layout from "../layout/layout"
import main from "../components/main"
import cen from "../views/score";
import Login from "../views/Login";
import Register from "../views/Register";

const routes = [
    {
        path: '/',
        name: 'Layout',
        component: Layout,
        redirect: "/main",
        children: [
            {
                path: '/main',
                name: 'main',
                component: main
            },
            {
                path: '/cen',
                name: 'cen',
                component: cen
            },

        ]
    },
    {
        path: '/login',
        name: 'Login',
        component:Login
    },

    {
        path: '/register',
        name: 'register',
        component:Register
    },

]

const router = createRouter({
    history: createWebHistory(process.env.BASE_URL),
    routes
})

export default router
