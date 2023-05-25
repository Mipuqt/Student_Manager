package com.example.demo.Contro;

import com.example.demo.common.Result;
import com.example.demo.entity.score;
import com.example.demo.entity.stuScore;
import com.example.demo.service.ScoreService;
import org.apache.ibatis.annotations.Param;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/score")
public class ScoreCon {
    @Autowired
    private ScoreService scoreService;

    @RequestMapping("/getall")
    public Result<?> selectAll(){
        List<Map<String,Object>> date=scoreService.getAll();
        return Result.success(date);
    }
    @PostMapping("/getstu")
    public Result<?> getstu(@Param("id") int id){
        System.out.println(id);
        List<Map<String,Object>> getScore = scoreService.getScore(id);
        return Result.success(getScore);
    }
    @PostMapping("/add")
    public Result<?> add(@RequestBody score score){
        int add = scoreService.InsertScore(score);
        return Result.success(add);

    }
    @PostMapping("/delete")
    public Result<?> delete(@Param("sid") int sid){
        Integer add = scoreService.DelScore(sid);
        return Result.success(add);
    }

    @PostMapping("/deleteex")
    public Result<?> deleteex(@Param("stype") String stype){
        Integer add = scoreService.DelEx(stype);
        return Result.success(add);
    }

    @PostMapping("/edit")
    public Result<?> edit(@RequestBody score score){
        System.out.println(score);
        Integer edit = scoreService.editScore(score);
        return Result.success(edit);

    }

    @PostMapping("/search")
    public Result<?> search(@RequestBody stuScore stuScore){
        System.out.println(stuScore);
        List<Map<String, Object>> search = scoreService.search(stuScore);
        System.out.println(stuScore);
        return Result.success(search);

    }
    @RequestMapping("/getex")
    public Result<?> getex(){
        List<Map<String,Object>> date=scoreService.getex();
        List<Map<String, Object>> transformedList = new ArrayList<>();
        for (Map<String, Object> map : date) {
            Map<String, Object> transformedMap = new HashMap<>();
            transformedMap.put("value", map.get("stype"));
            transformedMap.put("label", map.get("stype"));
            transformedList.add(transformedMap);
        }
        return Result.success(transformedList);
    }

    @RequestMapping("/getexinfo")
    public Result<?> getexinfo(){
        List<Map<String,Object>> date=scoreService.getexinfo();
        return Result.success(date);
    }

}
