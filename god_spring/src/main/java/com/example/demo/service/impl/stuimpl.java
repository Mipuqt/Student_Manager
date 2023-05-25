package com.example.demo.service.impl;

import com.example.demo.entity.stu;
import com.example.demo.mapper.StuMapper;
import com.example.demo.service.StuService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class stuimpl implements StuService {
    @Autowired
    private StuMapper stuMapper;

    @Override
    public List<stu> selectAll() {
       List<stu> rest=stuMapper.selectAll();
       return rest;
    }

    @Override
    public Integer InsertStu(stu stu) {
        int add=stuMapper.InsertStu(stu);
        return 1;
    }

    @Override
    public Integer DeleteStu(int id) {
        Integer delete=stuMapper.DeleteStu(id);
        return null;
    }

    @Override
    public List<stu> GetClass(String classroom) {
        List<stu> getclass1=stuMapper.getClass(classroom);
        return  getclass1;
    }

    @Override
    public List<stu> Getstu(int id) {
        List<stu> getclass1=stuMapper.Getstu(id);
        return  getclass1;
    }

    @Override
    public Integer editStu(stu stu) {
        Integer edit=stuMapper.editStu(stu);
        return 1;
    }


}
