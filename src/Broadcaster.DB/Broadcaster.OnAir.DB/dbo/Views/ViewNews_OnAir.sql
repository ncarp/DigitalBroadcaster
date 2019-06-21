
CREATE VIEW [dbo].[ViewNews_OnAir]
AS
SELECT dbo.NewsOnAir.ID, dbo.NewsOnAir.NewsID, 
    dbo.NewsOnAir.StartingDate, dbo.NewsOnAir.EndingDate, 
    Broadcaster.dbo.News.Name, Broadcaster.dbo.News.TypeID, 
    Broadcaster.dbo.TypeOfRM.Name AS Type
FROM dbo.NewsOnAir INNER JOIN
    Broadcaster.dbo.News ON 
    dbo.NewsOnAir.NewsID = Broadcaster.dbo.News.ID INNER JOIN
    Broadcaster.dbo.TypeOfRM ON 
    Broadcaster.dbo.News.TypeID = Broadcaster.dbo.TypeOfRM.ID

