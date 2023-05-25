package com.example.demo.service;

import com.example.demo.entity.stu;

import java.util.List;

public interface StuService {
    List<stu> selectAll();
    Integer InsertStu(stu stu);
    Integer DeleteStu(int id);
    List<stu> GetClass(String classroom);
    List<stu> Getstu(int id);
    Integer editStu(stu stu);

}
