
CREATE VIEW [dbo].[ViewTimeSignal]
AS
SELECT dbo.Time.ID, dbo.Time.Name, dbo.Time.FolderName, 
    dbo.HD.Path
FROM dbo.Time INNER JOIN
    dbo.HD ON dbo.Time.PathID = dbo.HD.ID



