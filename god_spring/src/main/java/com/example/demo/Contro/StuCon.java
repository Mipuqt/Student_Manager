package com.example.demo.Contro;

import com.example.demo.common.Result;
import com.example.demo.entity.stu;
import com.example.demo.service.StuService;
import org.apache.ibatis.annotations.Param;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
@RequestMapping("/main")
public class StuCon {
    @Autowired
    private StuService stuService;

    @RequestMapping("/studentInfo")
    public Result<?> selectAll() {
        List<stu> stuinfo = stuService.selectAll();
        return Result.success(stuinfo);
    }

    @PostMapping("/add")
    public Result<?> add(@RequestBody stu stu) {
        int add = stuService.InsertStu(stu);
        return Result.success(add);

    }

    @PostMapping("/edit")
    public Result<?> edit(@RequestBody stu stu) {
        int add = stuService.editStu(stu);
        return Result.success(add);

    }

    @PostMapping("/delete")
    public Result<?> delete(@Param("id") int id) {
        System.out.println(id);
        Integer add = stuService.DeleteStu(id);
        return Result.success(add);

    }

    @PostMapping("/getClass")
    public Result<?> getclass(@Param("classroom") String classroom) {
        System.out.println(classroom);
        List<stu> getClass = stuService.GetClass(classroom);
        return Result.success(getClass);
    }

    @PostMapping("/getstu")
    public Result<?> getstu(@Param("id") int id) {
        System.out.println(id);
        List<stu> getClass = stuService.Getstu(id);
        return Result.success(getClass);
    }
}
