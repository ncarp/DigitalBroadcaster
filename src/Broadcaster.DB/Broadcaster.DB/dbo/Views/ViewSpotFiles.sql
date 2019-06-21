
CREATE VIEW [dbo].[ViewSpotFiles]
AS
SELECT dbo.Spots.ID, RTRIM(dbo.HD.Path) 
    + '\' + RTRIM(dbo.Spots.FileName) AS FileName, 
    dbo.Spots.Activ
FROM dbo.Spots INNER JOIN
    dbo.HD ON dbo.Spots.PathID = dbo.HD.ID



