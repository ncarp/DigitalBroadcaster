
CREATE VIEW [dbo].[ViewScheduleTemplate]
AS
SELECT dbo.Scheduling.ItemOrder, dbo.Scheduling.ScheduleID, 
    dbo.SchedulingTemplate.Name, dbo.Scheduling.TemplateID, 
    dbo.Scheduling.ID, dbo.Scheduling.Date, 
    dbo.Scheduling.ItemType, dbo.Scheduling.ItemID, 
    dbo.SchedulingTemplate.strSQL
FROM dbo.Scheduling LEFT OUTER JOIN
    dbo.SchedulingTemplate ON 
    dbo.Scheduling.TemplateID = dbo.SchedulingTemplate.ID

