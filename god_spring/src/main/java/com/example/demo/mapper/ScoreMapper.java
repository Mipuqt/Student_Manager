package com.example.demo.mapper;

import com.example.demo.entity.score;
import com.example.demo.entity.stuScore;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;
import java.util.Map;

@Mapper
public interface ScoreMapper {
    List<Map<String,Object>> getAll();
    List<Map<String,Object>> getScore(@Param("id") int id);
    Integer InsertScore(score score);
    Integer editScore(score score);
    Integer delScore(@Param("sid") int sid);
    List<Map<String, Object>> search(stuScore stuScore);
    List<Map<String, Object>> getex();
    List<Map<String, Object>> getexinfo();
    Integer DelEX(@Param("stype") String stype);
}
