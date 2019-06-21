
CREATE VIEW [dbo].[ViewScheduledTime]
AS
SELECT     dbo.Scheduling.[Date], dbo.Scheduling.ItemOrder, dbo.Scheduling.ItemType, dbo.Scheduling.ItemID, dbo.Scheduling.ScheduleID, 
                      Broadcaster.dbo.Time.Name, 'Time' AS Type, dbo.Scheduling.TemplateID, dbo.SchedulingTemplate.Name AS TemplateName, 0 AS Start, 0 AS Intro, 
                      5000 AS Mix, 0 AS TypeID, dbo.Scheduling.Priority, 0 AS Rythm
FROM         dbo.Scheduling INNER JOIN
                      Broadcaster.dbo.Time ON dbo.Scheduling.ItemID = Broadcaster.dbo.Time.ID LEFT OUTER JOIN
                      dbo.SchedulingTemplate ON dbo.Scheduling.TemplateID = dbo.SchedulingTemplate.ID
WHERE     (dbo.Scheduling.ItemType = 58)

