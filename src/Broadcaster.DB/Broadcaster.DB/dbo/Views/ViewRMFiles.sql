
CREATE VIEW [dbo].[ViewRMFiles]
AS
SELECT dbo.RMs.ID, RTRIM(dbo.HD.Path) 
    + '\' + RTRIM(dbo.RMs.FileName) AS FileName
FROM dbo.RMs INNER JOIN
    dbo.HD ON dbo.RMs.PathID = dbo.HD.ID
WHERE (dbo.RMs.Activ = 1)



