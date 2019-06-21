CREATE VIEW [dbo].[ViewNews]
AS
SELECT     dbo.News.ID, dbo.News.Name, dbo.News.TypeID, dbo.News.[Date], dbo.News.Activ, dbo.News.NewsText, dbo.News.KeyWords, 
                      dbo.TypeOfRM.Name AS Type
FROM         dbo.News INNER JOIN
                      dbo.TypeOfRM ON dbo.News.TypeID = dbo.TypeOfRM.ID


