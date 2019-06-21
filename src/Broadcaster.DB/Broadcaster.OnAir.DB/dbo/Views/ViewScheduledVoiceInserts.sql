
CREATE VIEW [dbo].[ViewScheduledVoiceInserts]
AS
SELECT     dbo.Scheduling.[Date], dbo.Scheduling.ItemOrder, dbo.Scheduling.ItemType, dbo.Scheduling.ItemID, dbo.Scheduling.ScheduleID, 
                      dbo.VoiceInserts.Name, 'Take' AS Type, dbo.Scheduling.TemplateID, dbo.SchedulingTemplate.Name AS TemplateName, dbo.VoiceInserts.Start, 
                      0 AS Intro, dbo.VoiceInserts.Finish AS Mix, dbo.VoiceInserts.TalentID AS TypeID, dbo.Scheduling.Priority, 0 AS Rythm
FROM         dbo.Scheduling INNER JOIN
                      dbo.VoiceInserts ON dbo.Scheduling.ItemID = dbo.VoiceInserts.ID LEFT OUTER JOIN
                      dbo.SchedulingTemplate ON dbo.Scheduling.TemplateID = dbo.SchedulingTemplate.ID
WHERE     (dbo.Scheduling.ItemType = 54)

