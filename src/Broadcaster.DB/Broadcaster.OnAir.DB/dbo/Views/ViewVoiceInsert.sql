CREATE VIEW [dbo].[ViewVoiceInsert]
AS
SELECT     Broadcaster.dbo.OnAirUser.Name AS [User], dbo.VoiceInserts.ID, dbo.VoiceInserts.Name, dbo.VoiceInserts.FileName, dbo.VoiceInserts.Path, 
                      dbo.VoiceInserts.Start, dbo.VoiceInserts.Finish, dbo.VoiceInserts.TalentID, dbo.VoiceInserts.Activ, Broadcaster.dbo.HD.Path AS PathName
FROM         Broadcaster.dbo.OnAirUser INNER JOIN
                      dbo.VoiceInserts ON Broadcaster.dbo.OnAirUser.ID = dbo.VoiceInserts.TalentID LEFT OUTER JOIN
                      Broadcaster.dbo.HD ON dbo.VoiceInserts.Path = Broadcaster.dbo.HD.ID
