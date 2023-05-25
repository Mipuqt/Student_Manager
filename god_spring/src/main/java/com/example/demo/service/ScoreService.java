package com.example.demo.service;

import com.example.demo.entity.score;
import com.example.demo.entity.stuScore;

import java.util.List;
import java.util.Map;

public interface ScoreService {
  List<Map<String, Object>> getScore(int id);
  List<Map<String, Object>> getAll();
  int InsertScore(score score);
  Integer editScore(score score);
  List<Map<String, Object>> search(stuScore score);
  List<Map<String, Object>> getex();
  List<Map<String, Object>> getexinfo();
  Integer DelScore(int sid);
  Integer DelEx(String stype);
}
