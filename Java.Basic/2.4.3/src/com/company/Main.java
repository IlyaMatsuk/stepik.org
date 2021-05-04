package com.company;

import java.util.*;

public class Main {
    private static LinkedHashMap<String, ArrayList<String>> ParseRoles(String[] roles){
        LinkedHashMap<String, ArrayList<String>> map = new LinkedHashMap<>();
        for(int i = 0; i < roles.length; ++i){
            map.put(roles[i], new ArrayList<>());
        }
        return map;
    }
    private static void FillMap(LinkedHashMap<String, ArrayList<String>> rolesMap, String[] textLines){
        for(int i = 0; i < textLines.length; ++i){
            String[] splitStr = textLines[i].split(":", 2);
            if(rolesMap.containsKey(splitStr[0])){
                ArrayList<String> list = rolesMap.get(splitStr[0]);
                list.add(i+1 + ")" + splitStr[1] + "\n");
            }
        }
    }

    private static String CreateOutputStr(LinkedHashMap<String, ArrayList<String>> rolesMap){
        StringBuilder output = new StringBuilder();
        for(Map.Entry<String, ArrayList<String>> entry: rolesMap.entrySet()){
            output.append(entry.getKey() + ":\n");
            for(int i = 0; i < entry.getValue().size(); ++i){
                output.append(entry.getValue().get(i));
            }
            output.append("\n");
        }
        return output.toString();
    }

    private static String printTextPerRole(String[] roles, String[] textLines) {
        LinkedHashMap<String, ArrayList<String>> rolesMap = ParseRoles(roles);
        FillMap(rolesMap, textLines);
        return CreateOutputStr(rolesMap);
    }

    public static void main(String[] args) {
        String[] roles = {
                "Городничий",
                "Аммос Федорович",
                "Артемий Филиппович",
                "Лука Лукич"
        };
        String[] textLines = {
                "Городничий: Я пригласил вас, господа, с тем, чтобы сообщить вам пренеприятное известие: к нам едет ревизор.",
                "Аммос Федорович: Как ревизор?",
                "Артемий Филиппович: Как ревизор?",
                "Городничий: Ревизор из Петербурга, инкогнито. И еще с секретным предписаньем.",
                "Аммос Федорович: Вот те на!",
                "Артемий Филиппович: Вот не было заботы, так подай!",
                "Лука Лукич: Господи боже! еще и с секретным предписаньем!"
        };
        String str = printTextPerRole(roles, textLines);
        System.out.println(str);
    }
}
