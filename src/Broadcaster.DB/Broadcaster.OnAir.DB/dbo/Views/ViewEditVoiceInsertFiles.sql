
CREATE VIEW [dbo].[ViewEditVoiceInsertFiles]
AS
SELECT RTRIM(Broadcaster.dbo.HD.Path) 
    + '\' + RTRIM(dbo.VoiceInserts.FileName) AS FileName, 
    dbo.VoiceInserts.ID
FROM Broadcaster.dbo.HD INNER JOIN
    dbo.VoiceInserts ON 
    Broadcaster.dbo.HD.ID = dbo.VoiceInserts.Path
WHERE (dbo.VoiceInserts.Activ = 1)

