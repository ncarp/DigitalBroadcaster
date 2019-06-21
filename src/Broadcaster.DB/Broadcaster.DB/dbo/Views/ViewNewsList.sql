
CREATE VIEW [dbo].[ViewNewsList]
AS
SELECT dbo.News.ID, dbo.News.Name, dbo.News.TypeID, 
    dbo.TypeOfRM.Name AS Type
FROM dbo.News INNER JOIN
    dbo.TypeOfRM ON 
    dbo.News.TypeID = dbo.TypeOfRM.ID
WHERE (dbo.News.Activ = 1)



