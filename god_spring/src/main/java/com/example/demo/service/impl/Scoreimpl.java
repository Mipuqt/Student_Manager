package com.example.demo.service.impl;

import com.example.demo.entity.score;
import com.example.demo.entity.stuScore;
import com.example.demo.mapper.ScoreMapper;
import com.example.demo.service.ScoreService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Map;

@Service
public class Scoreimpl implements ScoreService {
    @Autowired
    private ScoreMapper scoreMapper;
    @Override
    public List<Map<String, Object>> getScore(int id) {
        List<Map<String,Object>> date=scoreMapper.getScore(id);
        return date;
    }

    @Override
    public List<Map<String, Object>> getAll() {
        List<Map<String,Object>> date=scoreMapper.getAll();
        return date;
    }

    @Override
    public int InsertScore(score score) {
        Integer re=scoreMapper.InsertScore(score);
        return  1;
    }

    @Override
    public Integer editScore(score score) {
        Integer re =scoreMapper.editScore(score);
        return 1;
    }

    @Override
    public List<Map<String, Object>> search(stuScore score) {
        List<Map<String, Object>> search = scoreMapper.search(score);
        return search;
        }

    @Override
    public List<Map<String, Object>> getex() {
        List<Map<String, Object>> date = scoreMapper.getex();
        return date;
    }

    @Override
    public List<Map<String, Object>> getexinfo() {
        List<Map<String, Object>> date = scoreMapper.getexinfo();
        return date;
    }

    @Override
    public Integer DelScore(int sid) {
        Integer  delaction =scoreMapper.delScore(sid);
        return 1;
    }

    @Override
    public Integer DelEx(String stype) {
        Integer  delaction =scoreMapper.DelEX(stype);
        return 1;
    }
}
