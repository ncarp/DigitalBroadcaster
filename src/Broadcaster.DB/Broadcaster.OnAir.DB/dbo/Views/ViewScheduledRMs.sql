
CREATE VIEW [dbo].[ViewScheduledRMs]
AS
SELECT     dbo.Scheduling.[Date], dbo.Scheduling.ItemOrder, dbo.Scheduling.ItemType, dbo.Scheduling.ItemID, dbo.Scheduling.ScheduleID, 
                      Broadcaster.dbo.TypeOfRM.Name AS Type, Broadcaster.dbo.RMs.Name, dbo.Scheduling.TemplateID, dbo.SchedulingTemplate.Name AS TemplateName, 
                      Broadcaster.dbo.RMs.Start, 0 AS Intro, Broadcaster.dbo.RMs.Mix, Broadcaster.dbo.TypeOfRM.ID AS TypeID, dbo.Scheduling.Priority, 0 AS rythm
FROM         Broadcaster.dbo.TypeOfRM INNER JOIN
                      Broadcaster.dbo.RMs ON Broadcaster.dbo.TypeOfRM.ID = Broadcaster.dbo.RMs.TypeID INNER JOIN
                      dbo.Scheduling ON Broadcaster.dbo.RMs.ID = dbo.Scheduling.ItemID LEFT OUTER JOIN
                      dbo.SchedulingTemplate ON dbo.Scheduling.TemplateID = dbo.SchedulingTemplate.ID
WHERE     (dbo.Scheduling.ItemType = 57)

