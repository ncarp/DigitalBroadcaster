
CREATE VIEW [dbo].[ViewScheduledSpots]
AS
SELECT     dbo.Scheduling.[Date], dbo.Scheduling.ItemOrder, dbo.Scheduling.ItemType, dbo.Scheduling.ItemID, dbo.Scheduling.ScheduleID, 
                      Broadcaster.dbo.Spots.Name, Broadcaster.dbo.Customers.Name AS Type, dbo.Scheduling.TemplateID, dbo.SchedulingTemplate.Name AS TemplateName, 
                      Broadcaster.dbo.Spots.Start, 0 AS Intro, Broadcaster.dbo.Spots.Mix, Broadcaster.dbo.Customers.ID AS TypeID, dbo.Scheduling.Priority, 0 AS Rythm
FROM         dbo.Scheduling INNER JOIN
                      Broadcaster.dbo.Spots ON dbo.Scheduling.ItemID = Broadcaster.dbo.Spots.ID INNER JOIN
                      Broadcaster.dbo.Customers ON Broadcaster.dbo.Spots.CustomerID = Broadcaster.dbo.Customers.ID LEFT OUTER JOIN
                      dbo.SchedulingTemplate ON dbo.Scheduling.TemplateID = dbo.SchedulingTemplate.ID
WHERE     (dbo.Scheduling.ItemType = 53)

