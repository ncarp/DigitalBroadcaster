CREATE VIEW [dbo].[ViewWorkingSchedule]
AS
SELECT     dbo.Scheduling.ID, dbo.Scheduling.ItemType, dbo.Scheduling.ItemID, dbo.Scheduling.ScheduleID, dbo.Scheduling.Priority, dbo.Scheduling.TemplateID, 
                      dbo.SchedulingTemplate.strSQL, dbo.Scheduling.ItemOrder, dbo.Scheduling.ItemParentID, dbo.SchedulingTemplate.Name, 
                      dbo.SchedulingTemplate.ArtistQuarantine, dbo.SchedulingTemplate.SongQuarantine, dbo.SchedulingTemplate.RandomFactor, 
                      dbo.SchedulingTemplate.LastPos
FROM         dbo.Scheduling LEFT OUTER JOIN
                      dbo.SchedulingTemplate ON dbo.Scheduling.TemplateID = dbo.SchedulingTemplate.ID
