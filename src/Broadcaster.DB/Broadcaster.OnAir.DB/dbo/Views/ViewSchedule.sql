
CREATE VIEW [dbo].[ViewSchedule]
AS
SELECT *
FROM ViewScheduledMusic
UNION
(SELECT *
FROM ViewScheduledJingles)
UNION
(SELECT *
FROM ViewScheduledSpots)
UNION
(SELECT *
FROM ViewScheduledVoiceInserts)
UNION
(SELECT *
FROM ViewScheduledTime)
UNION
(SELECT *
FROM ViewScheduledRMs)



