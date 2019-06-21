
CREATE VIEW [dbo].[ViewJingleFiles]
AS
SELECT dbo.Jingles.ID, RTRIM(dbo.HD.Path) 
    + '\' + RTRIM(dbo.Jingles.FileName) AS FileName
FROM dbo.Jingles INNER JOIN
    dbo.HD ON dbo.Jingles.PathID = dbo.HD.ID
WHERE (dbo.Jingles.Activ = 1)



