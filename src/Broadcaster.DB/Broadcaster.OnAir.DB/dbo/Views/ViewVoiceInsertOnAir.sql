
CREATE VIEW [dbo].[ViewVoiceInsertOnAir]
AS
SELECT VoiceInserts.ID, VoiceInserts.Name, VoiceInserts.FileName, 
    Broadcaster.dbo.HD.Path, VoiceInserts.Start, 
    VoiceInserts.Finish
FROM VoiceInserts INNER JOIN
    Broadcaster.dbo.HD ON VoiceInserts.Path = Broadcaster.dbo.HD.ID

