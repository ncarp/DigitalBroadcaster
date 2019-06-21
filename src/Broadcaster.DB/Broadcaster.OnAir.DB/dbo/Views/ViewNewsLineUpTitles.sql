
CREATE VIEW [dbo].[ViewNewsLineUpTitles]
AS
SELECT dbo.NewsLineUpComponents.LineUpID, 
    dbo.NewsLineUpComponents.Position, 
    RTRIM(Broadcaster.dbo.TypeOfRM.Name) 
    + ' - ' + RTRIM(Broadcaster.dbo.News.Name) AS News, 
    dbo.NewsLineUpComponents.NewsID
FROM dbo.NewsLineUpComponents INNER JOIN
    Broadcaster.dbo.News ON 
    dbo.NewsLineUpComponents.NewsID = Broadcaster.dbo.News.ID INNER
     JOIN
    Broadcaster.dbo.TypeOfRM ON 
    Broadcaster.dbo.News.TypeID = Broadcaster.dbo.TypeOfRM.ID

