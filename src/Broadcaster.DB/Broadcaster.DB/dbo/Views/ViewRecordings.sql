
CREATE VIEW [dbo].[ViewRecordings]
AS
SELECT dbo.RecordingTask.ID, dbo.RecordingTask.Name, 
    dbo.RecordingTask.TalentID, dbo.RecordingTask.Deadline, 
    dbo.RecordingTask.Todo, dbo.RecordingTask.Completed, 
    dbo.RecordingVersion.ID AS VersionID, 
    dbo.RecordingVersion.FileName, 
    dbo.RecordingVersion.PathID, dbo.RecordingVersion.Remarks, 
    dbo.RecordingVersion.Deleted, dbo.HD.Path, 
    dbo.RecordingVersion.Name AS VersionName
FROM dbo.HD INNER JOIN
    dbo.RecordingVersion ON 
    dbo.HD.ID = dbo.RecordingVersion.PathID RIGHT OUTER JOIN
    dbo.RecordingTask ON 
    dbo.RecordingVersion.RecordingID = dbo.RecordingTask.ID



