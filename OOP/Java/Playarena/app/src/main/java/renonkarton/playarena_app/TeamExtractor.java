package renonkarton.playarena_app;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Element;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;

import org.jsoup.nodes.Document;
import org.jsoup.select.Elements;
public class TeamExtractor {

    private static int StringToInt(String enter) //with dot!
    {
        int x = 0;
        for (int j = 0; true; j++) {
            if (enter.length() == j || enter.charAt(j) == '.') break;
            x *= 10;
            x += enter.charAt(j) - '0';
        }
        return x;
    }

    //url docelowo ma byc podawane w argumencie, zeby wiecej tabeli moznabylo przerobic
    public static Team[] getTeams(String url) throws IOException, ExecutionException, InterruptedException {
        //exectute tworzy ten watek w oparciu o ten link, a potem get wywala wartosc
        Document doc = (new TableDownloader()).execute("http://playarena.pl/leagueSeason/ajaxTable?league_season_id=" + url).get();
        Elements team_list = doc.getElementsByTag("tr");
        List<Team> result = new ArrayList<Team>();
        for (int i = 1; i < 100; i++) {
            //Tu mamy caly html dotyczacy jednego klubu
            Element team_data = team_list.get(i);
            // System.out.print(team_data.toString());
            //Wszystkie rzeczy z atrybutem class to te rzeczy, ktore chcemy - pozycja w tabeli/nazwa/punkty i bramki
            Elements important_data = team_data.getElementsByAttribute("class");
            if(important_data.size()==0 || important_data.get(0).text().equals("Pozycja")) break;
            //a no ciekawostka jest tez taka, ze jest to dwukrotnie
            //System.out.println(important_data.text());

            //pozycja w tabeli jest pierwsza
            String position_text = important_data.get(1).text();
            //nazwa jest trzecia
            //Url jest w atrybucie/id, wiec trza sie inaczej do niego dobrac
            String teamUrl = important_data.attr("href");
            String logoUrl = logo_url_cutter(important_data.get(2).html());
            String name = important_data.get(3).text();
            //punkty sa dziewiate
            int points = StringToInt(important_data.get(9).text());
            //szybki konwerter
            int position = StringToInt(position_text);
            result.add( new Team(name, position, points,  teamUrl, logoUrl));
        }
        return result.toArray(new Team[result.size()]);
    }


    private static String logo_url_cutter(String url) {
        String result = "";
        boolean p = false;
        StringBuilder bd = new StringBuilder(result);
        for (int i = 0; true; i++)
        {
            if(url.charAt(i) == ')') break;
            if(p)  bd.append(url.charAt(i));
            if(url.charAt(i) == '(') p = true;
        }
        return bd.toString();
    }

    public static void main(String argv[]) throws IOException, InterruptedException, ExecutionException {
        //     Team[] teams_array = TeamExtractor.getTeams("http://playarena.pl/leagueSeason/ajaxTable?league_season_id=15681");
        Document doc = Jsoup.connect("http://playarena.pl/leagueSeason/ajaxTable?league_season_id=15613").get();
        // Document doc =  (new TableDownloader()).execute(url).get();
        Elements team_list = doc.getElementsByTag("tr");
       // System.out.println(team_list.toString());
        Team[] result = new Team[14];
        Elements important_data = team_list.get(13).getElementsByAttribute("class");
        System.out.println(logo_url_cutter(team_list.get(2).getElementsByAttribute("class").get(2).html()));
        /*for(int i = 1; i < 15; i++)
        {
            //Tu mamy caly html dotyczacy jednego klubu
            Element team_data = team_list.get(i);
           // System.out.print(team_data.toString());
            //Wszystkie rzeczy z atrybutem class to te rzeczy, ktore chcemy - pozycja w tabeli/nazwa/punkty i bramki
            Elements important_data = team_data.getElementsByAttribute("class");
            //a no ciekawostka jest tez taka, ze jest to dwukrotnie xD
            System.out.println(important_data.toString());

            //pozycja w tabeli jest pierwsza
            String position_text = important_data.get(1).text();
            //nazwa jest trzecia
            String name = important_data.get(3).text();
            //Url jest w atrybucie/id, wiec trza sie inaczej do niego dobrac
            String url = important_data.attr("href");
            //System.out.println(url);
            //punkty sa dziewiate
            int points = StringToInt(important_data.get(9).text());
            //szybki konwerter
            int position = StringToInt(position_text);
            result[i-1] = new Team(name,position, points,  url);
            System.out.println(result[i-1].teamUrl.toString());
        }*/
    }
}
