
CREATE VIEW [dbo].[ViewJinglesSmallList]
AS
SELECT dbo.Jingles.ID, RTRIM(dbo.TypeOfJingle.Name) 
    + ' - ' + RTRIM(dbo.Jingles.Name) AS Jingle
FROM dbo.Jingles INNER JOIN
    dbo.TypeOfJingle ON 
    dbo.Jingles.TypeID = dbo.TypeOfJingle.ID



