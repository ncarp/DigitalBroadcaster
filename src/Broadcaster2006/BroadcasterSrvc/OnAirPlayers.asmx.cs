using System;
using System.Data;
using System.Data.Odbc;
using System.Web;
using System.Collections;
using System.Web.Services;
using System.Web.Services.Protocols;
using System.ComponentModel; 

namespace BroadcasterSrvc
{
    /// <summary>
    /// Summary description for BroadacasterService1
    /// </summary>
    /// 

    public struct PlayerInfo
    {
        public int PlayerN;
        public long ItemType;
        public long ItemID;
        public long ItemParentID;
        public string ItemName1;
        public string ItemName2;
    }

    public struct ScheduleInfo
    {
        public int ScheduleID;
        public string Name;
        public DateTime DateStart;
        public DateTime DateFinish;
        public SongInfo[] Songs;
    }

    public struct SongInfo
    {
        public DateTime Time;
        public long SongID;
        public string ArtistName;
        public string Title;
    }

    public struct ERCRATIO
    {
        public String ALIAS;
        
        public String Date;
        public CollectionBase PLAYLIST;
    }

    public struct PlayList
    {
        public String DATE;
        public Song [] SONG;
    }

    public struct Song 
    {
        public String TIME;
        public int DURATION;
        public String ARTIST;
        public String MUSICTRACK;
        public String NATIONALITY;
        public String EXPRESSION;
        public String YEAR;
        public int PORTUGUESEM;
        public String GENRE;
        public String ISRC;
    }

    [WebService(Namespace = "http://high-precision.pt/")]
    [ToolboxItem(false)]
    public class BroadacasterService1 : System.Web.Services.WebService
    {

        [WebMethod]
        public string Hello()
        {
            return "Saudações do Digital Broadcaster";
        }

        [WebMethod]
        public PlayerInfo[] GetPlayers()
        {
            PlayerInfo [] Players=null;

            DataSetOnAirTableAdapters.PlayersTableAdapter pta=new DataSetOnAirTableAdapters.PlayersTableAdapter();
            DataSetOnAir.PlayersDataTable pt = new DataSetOnAir.PlayersDataTable() ;

            pta.Fill(pt);

            Players = new PlayerInfo[pt.Rows.Count];
            int i = 0;

            foreach (DataSetOnAir.PlayersRow r in pt.Rows )
            {
                Players[i].PlayerN = r.Order;
                Players[i].ItemType = r.ItemType;
                Players[i].ItemID = r.ItemID;
                Players[i].ItemParentID = r.ArtistID;
                Players[i].ItemName1 = r.ArtistName;
                Players[i].ItemName2 = r.TrackTitle;
                i++;
            }
            return Players;
        }

        [WebMethod]
        public ScheduleInfo[] GetDaySchedule(DateTime date)
        {
            DateTime finish=date+new TimeSpan(1,0,0,0);
            String strSQL = String.Format("SELECT ID,[Date],EndingDate, Name FROM SchedulingHeadlines WHERE [Date]>='{0}-{1}-{2}' and [Date]<'{3}-{4}-{5}'",
                date.Year, date.Month, date.Day,
                finish.Year, finish.Month, finish.Day);
                

            ScheduleInfo [] DaySchedule = null;
            OdbcConnection odbcConn = new OdbcConnection("DSN=Broadcaster-OnAir");
            OdbcDataAdapter odbcDataAdapter = new OdbcDataAdapter(strSQL, odbcConn);
            DataSet ds=new DataSet();
            int i = 0;

            odbcDataAdapter.Fill(ds);

            DaySchedule = new ScheduleInfo[ds.Tables[0].Rows.Count];

            foreach (DataRow pRow in ds.Tables[0].Rows)
            {
                DaySchedule[i].ScheduleID = (int)pRow["ID"];
                DaySchedule[i].Name = pRow["Name"].ToString();
                DaySchedule[i].DateStart = (DateTime)pRow["Date"];
                DaySchedule[i].DateFinish = (DateTime)pRow["EndingDate"];

                OdbcDataAdapter dataAdapterSongs = new OdbcDataAdapter("SELECT [Date],ItemID,Type,Name FROM ViewScheduledMusic WHERE ScheduleID="+pRow["ID"]+" ORDER BY ItemOrder",odbcConn);
                DataSet dataSetSongs = new DataSet();
                int nSong = 0;

                dataAdapterSongs.Fill(dataSetSongs);
                DaySchedule[i].Songs = new SongInfo[dataSetSongs.Tables[0].Rows.Count];

                foreach (DataRow pSong in dataSetSongs.Tables[0].Rows)
                {
                    DaySchedule[i].Songs[nSong].Time = (DateTime)pSong["Date"];
                    DaySchedule[i].Songs[nSong].ArtistName = pSong["Type"].ToString();
                    DaySchedule[i].Songs[nSong].SongID = (int)pSong["ItemID"];
                    DaySchedule[i].Songs[nSong].Title = pSong["Name"].ToString();

                    nSong++;
                }

                dataSetSongs = null;
                dataAdapterSongs = null;

                i++;
            }
            return DaySchedule;
        }

        /*
        [WebMethod]
        public ERCRATIO GetErcRatio(DateTime date)
        {
            ERCRATIO erc;

            erc.

            DateTime date2 = date+new TimeSpan(1,0,0,0);
            DateTime Year;
            String strSQL = String.Format("SELECT * FROM ViewERC WHERE AirDate>='{0}-{1}-{2}' AND AirDate<'{3}-{4}-{5}'",
                date.Year, date.Month, date.Day,
                date2.Year, date2.Month, date2.Day);

            erc.PLAYLIST = null;
            OdbcConnection odbcConn = new OdbcConnection("DSN=Broadcaster-OnAir");
            OdbcDataAdapter odbcDataAdapter = new OdbcDataAdapter(strSQL, odbcConn);
            DataSet ds = new DataSet();
            int i = 0;
            
            odbcDataAdapter.Fill(ds);

            erc.ALIAS = "TESTE";

            erc.PLAYLIST = new ArrayList() ;
            erc.Date = "2000-01-01";

            Song [] newSong = null;

            foreach (DataRow Row in ds.Tables[0].Rows)
            {
                Year = (DateTime)Row["RecordingDate"];
                newSong = new Song();

                newSong.ARTIST = Row["Artist"].ToString();
                newSong.DURATION = (int)Row["Length"];
                erc.PLAYLIST[i].EXPRESSION = Row["LangCode"].ToString();
                erc.PLAYLIST[i].GENRE = Row["Category"].ToString();
                erc.PLAYLIST[i].ISRC = "";
                erc.PLAYLIST[i].MUSICTRACK = Row["Title"].ToString();
                erc.PLAYLIST[i].NATIONALITY = Row["NatCode"].ToString();
                if ((erc.PLAYLIST[i].EXPRESSION == "pt") && ((int)Row["EU"] == 1))
                    erc.PLAYLIST[i].PORTUGUESEM = 1;
                else
                    erc.PLAYLIST[i].PORTUGUESEM = 0;
                erc.PLAYLIST[i].PORTUGUESEM = 0;
                erc.PLAYLIST[i].YEAR = Year.Year.ToString() + "-" + Year.Month.ToString() + "-" + Year.Day.ToString();

                erc.PLAYLIST.Add(newSong);

                i++;
            }

            return erc;
        } */
    }
}
