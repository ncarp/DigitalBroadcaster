
CREATE VIEW [dbo].[ViewScheduledJingles]
AS
SELECT     dbo.Scheduling.[Date], dbo.Scheduling.ItemOrder, dbo.Scheduling.ItemType, dbo.Scheduling.ItemID, dbo.Scheduling.ScheduleID, 
                      Broadcaster.dbo.TypeOfJingle.Name AS Type, Broadcaster.dbo.Jingles.Name, dbo.Scheduling.TemplateID, 
                      dbo.SchedulingTemplate.Name AS TemplateName, Broadcaster.dbo.Jingles.Start, Broadcaster.dbo.Jingles.Intro, Broadcaster.dbo.Jingles.Mix, 
                      Broadcaster.dbo.TypeOfJingle.ID AS TypeID, dbo.Scheduling.Priority, Broadcaster.dbo.Jingles.Rythm
FROM         Broadcaster.dbo.TypeOfJingle INNER JOIN
                      Broadcaster.dbo.Jingles ON Broadcaster.dbo.TypeOfJingle.ID = Broadcaster.dbo.Jingles.TypeID INNER JOIN
                      dbo.Scheduling ON Broadcaster.dbo.Jingles.ID = dbo.Scheduling.ItemID LEFT OUTER JOIN
                      dbo.SchedulingTemplate ON dbo.Scheduling.TemplateID = dbo.SchedulingTemplate.ID
WHERE     (dbo.Scheduling.ItemType = 52)

