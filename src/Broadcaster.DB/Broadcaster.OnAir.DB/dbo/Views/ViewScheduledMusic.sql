
CREATE VIEW [dbo].[ViewScheduledMusic]
AS
SELECT     dbo.Scheduling.[Date], dbo.Scheduling.ItemOrder, dbo.Scheduling.ItemType, dbo.Scheduling.ItemID, dbo.Scheduling.ScheduleID, 
                      Broadcaster.dbo.Artists.Name AS Type, Broadcaster.dbo.MusicTracks.Title AS Name, dbo.Scheduling.TemplateID, 
                      dbo.SchedulingTemplate.Name AS TemplateName, Broadcaster.dbo.MusicTracks.Start, Broadcaster.dbo.MusicTracks.Intro, 
                      Broadcaster.dbo.MusicTracks.Mix, Broadcaster.dbo.Artists.ID AS TypeID, dbo.Scheduling.Priority, Broadcaster.dbo.MusicTracks.Rythm
FROM         Broadcaster.dbo.MusicTracks INNER JOIN
                      Broadcaster.dbo.Artists ON Broadcaster.dbo.MusicTracks.ArtistID = Broadcaster.dbo.Artists.ID INNER JOIN
                      dbo.Scheduling ON Broadcaster.dbo.MusicTracks.ID = dbo.Scheduling.ItemID LEFT OUTER JOIN
                      dbo.SchedulingTemplate ON dbo.Scheduling.TemplateID = dbo.SchedulingTemplate.ID
WHERE     (dbo.Scheduling.ItemType = 51)

