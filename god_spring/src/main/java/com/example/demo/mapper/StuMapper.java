package com.example.demo.mapper;

import com.example.demo.entity.stu;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

@Mapper
public interface StuMapper {
    List<stu> selectAll();
    Integer InsertStu(stu stu);
    Integer DeleteStu(@Param("id") int id);
    List<stu> getClass(@Param("classroom")String classroom);
    List<stu> Getstu(@Param("id") int id);
    Integer editStu(stu stu);
}
